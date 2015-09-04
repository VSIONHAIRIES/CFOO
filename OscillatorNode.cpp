#include "OscillatorNode.h"

#include <Arduino.h>

#define BIT_32 4294967296
#define PERIOD_MAX BIT_32 /// need to move this
#define SAMPLE_RATE 48000 /// need to move this

const uint16_t waveTable[] = { 
#include <FrictionWaveTable.inc>
};

const extern uint32_t portamentoTimeTable[] = {1,5,9,13,17,21,26,30,35,39,44,49,54,59,64,69,74,79,85,90,96,101,107,113,119,125,132,138,144,151,158,165,172,179,187,194,202,210,218,226,234,243,252,261,270,279,289,299,309,320,330,341,353,364,376,388,401,414,427,440,455,469,484,500,516,532,549,566,584,602,622,642,663,684,706,729,753,778,804,831,859,888,919,951,984,1019,1056,1094,1134,1176,1221,1268,1317,1370,1425,1484,1547,1614,1684,1760,1841,1929,2023,2125,2234,2354,2484,2627,2785,2959,3152,3368,3611,3886,4201,4563,4987,5487,6087,6821,7739,8918,10491,12693,15996,21500,32509,65535};

OscillatorNode::OscillatorNode(AudioContext* audioContext, WaveformType wavetype) : AudioNode(audioContext), AudioSourceNode() {

	_period = 0;
	_phase = 0;
	_osc = 0;
	_sample = 0;
	_accumulator = 0;
	_index = 0;
	
	setWaveform(wavetype);

	_freq = 150;
	frequency.value = _freq;
	frequency.value.reset();

	setFrequency(_freq);

	_detune = 0;
	detune.value = _detune;
	detune.value.reset();

	_portamento = 1;
	portamento.value = _portamento;
	portamento.value.reset();

	_gain = 65535;
	gain.value = 1.0f;
	gain.value.reset();

}

void OscillatorNode::setWaveform(WaveformType wavetype) {
	type.value = wavetype;
	_osc_wave_ptr = &waveTable[wavetype * 256];
}

void OscillatorNode::setFrequency(float freq) {
	_freq = freq;
	frequency.value = _freq;
	//_period = int32_t(((_freq * (1 + _detune)) * PERIOD_MAX) / _audioCtx->sample_rate());
	_period = int32_t(((_freq * (1 + _detune)) * PERIOD_MAX) / SAMPLE_RATE);
}

void OscillatorNode::process(int64_t& sample) {

	if(!_processing) {
		sample = 0;
		return;
	}

	// needs optimisation --- these should be k-rate or a-rate...
	if(frequency.value.updated() && frequency.val() != _freq) {
		setFrequency(frequency.val());
		frequency.value.reset();
	}
	if(detune.value.updated() && detune.val() != _detune) {
		_detune = detune.val();
		detune.value.reset();
	}
	if(portamento.value.updated() && portamento.val() != _portamento) {
		_portamento = portamento.val();
		portamento.value.reset();
	}
	if(gain.value.updated()) {
		_gain = uint16_t(gain.val() * 65535);
		gain.value.reset();
	}

	_phase = _phase + (_period - _phase) / _portamento;
	_accumulator = _accumulator + _phase;
	_index = _accumulator >> 24;

	_osc = *(_osc_wave_ptr + _index);
	_osc -= 128;
	_osc <<= 8;
	_sample = (_osc * _gain);  
	
	_sample >>= 18;

	sample = _sample;

}

/*

void inline MMusic::setFrequency1(float freq)
{
	frequency1 = freq;
	period1 = int32_t(((frequency1 * semi1 * (1 + detune1 + bend)) * PERIOD_MAX) / SAMPLE_RATE);
}

void MMusic::setDetune(float detune)
 {
 	detune1 = 0.0;
 }

 void MMusic::setPortamento(int32_t port) {
	if(port == 0) port = 1;
	portamento = port;
//	portamento = envTimeTable[uint8_t(port)];
}


*/