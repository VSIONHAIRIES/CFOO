#include "GainNode.h"
#include <algorithm>

#include <Arduino.h>

void GainNode::connect(AudioNode* destination) {
	if(_output == NULL) {
		_node_outputs.push_back(destination);
		destination->hook(this);
		_output = destination;
	}
}

void GainNode::disconnect(AudioNode* destination) {
	if(_output != NULL && _output == destination) {
		_node_outputs.erase(std::remove(_node_outputs.begin(), _node_outputs.end(), destination), _node_outputs.end());
		destination->unhook(this); // no lookup first??
		_output = NULL;
	}
}

void GainNode::hook(AudioNode* input) {
	if(_input == NULL) {
		_node_inputs.push_back(input);
		_input = input;
	}
}

void GainNode::unhook(AudioNode* destination) {
	if(_input != NULL && _input == destination) {
		_node_inputs.erase(std::remove(_node_inputs.begin(), _node_inputs.end(), destination), _node_inputs.end());	
		_input = NULL;
	}
}


void GainNode::process(int64_t& sample) {	
	if(_input != NULL) {		
		static int64_t s = 0;
		static uint16_t g = 0;
		_input->process(s);
		g = uint16_t(gain.val() * 65535);
		sample = g * s;
		//sample = s;
	}
}