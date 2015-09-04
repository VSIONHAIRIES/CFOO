#pragma once

#include "AudioSourceNode.h"
#include "AudioParam.h"
#include <stdint.h>

enum WaveformType {
SINE  = 0
, SQUARE = 1
, PULSE = 2
, TRIANGLE = 3
, SAW = 4
, FUZZ = 5
, DIGI1 = 6
, DIGI2 = 7
, DIGI3 = 8
, DIGI4 = 9
, NOISE = 10
, DIGI6 = 11
, TAN1 = 12
, TAN2 = 13
, TAN3 = 14
, TAN4 = 15
};

class OscillatorNode : public AudioSourceNode {
public:

	OscillatorNode(AudioContext* audioContext, WaveformType wavetype = SINE);

	void process(int64_t& sample) override;

	void setWaveform(WaveformType wavetype);
	void setFrequency(float freq);

	inline void start() { _processing = true; }
	inline void stop() { _processing = false; }

	AudioParam<WaveformType> 	type;
	AudioParamFloat 			frequency;
	AudioParamFloat 			detune;
	AudioParam<int32_t>			portamento;
	AudioParamFloat 			gain;

	//AudioParamFloat 			gain; --- GainNode vs GainParam??

protected:

	WaveformType 	_type;
	float 			_freq;
	float 			_detune;
	int32_t 		_portamento;
	uint16_t		_gain;	

	int32_t 		_period;
	int32_t			_phase;
	int32_t			_osc;	
	uint32_t 		_accumulator;
	int32_t			_index;
	
	const uint16_t* _osc_wave_ptr;

	int64_t	_sample;

	bool			_processing = false;
	

};