#include "AudioContext.h"

#include <Arduino.h>

AudioDestinationNode_T3DAC t3dac_destinationNode(NULL);

AudioContext::AudioContext() {
	destination_ptr = &t3dac_destinationNode;	
}

GainNode* AudioContext::createGain() {
	GainNode* n = new GainNode(this);
	_nodes.push_back(n);
	return n;
}

OscillatorNode* AudioContext::createOscillator() {
	OscillatorNode* n = new OscillatorNode(this);
	_nodes.push_back(n);
	return n;
}

AudioDestinationNode* AudioContext::destination() {
	return destination_ptr;
}

int AudioContext::sample_rate() {
	return 	destination_ptr->sample_rate();
}