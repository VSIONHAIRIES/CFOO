#include "AudioDestinationNode_T3DAC.h"

#include <Arduino.h>

#define SAMPLE_RATE 48000
#define CPU_FREQ 96 // in MHz

IntervalTimer synthTimer;

void synth_isr();

AudioDestinationNode_T3DAC::AudioDestinationNode_T3DAC(AudioContext* audioContext) 
	: AudioNode(audioContext), AudioDestinationNode(), _sample(0) {

	analogWriteResolution(12);

	cli();
	synthTimer.begin(synth_isr, 1000000.0 / SAMPLE_RATE);
	sei();

}

void AudioDestinationNode_T3DAC::isr(void) {	


	_sample += 32768;
	analogWrite(A14, _sample>>4);

	_sample = 0;

	// http://fastcpp.blogspot.nl/2011/03/fast-iteration-over-stl-vector-elements.html
	const int n = _node_inputs.size();
	if(n == 0) return;
	AudioNode** ptr = &_node_inputs.front();
	for(int i = 0; i < n; i++) {
		ptr[i]->process(_accum);
		_sample += _accum;
	}

	// for(unsigned int i = 0; i < _node_inputs.size(); i++) {
	// 	_node_inputs[i]->process(_accum);
	// 	_sample += _accum;		
	// }

	//_sample >>= 18; // hmmm....

}

int AudioDestinationNode_T3DAC::sample_rate() {
	return SAMPLE_RATE;
}

void synth_isr() {	
	t3dac_destinationNode.isr();
}

