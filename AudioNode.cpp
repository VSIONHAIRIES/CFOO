#include "AudioNode.h"
#include <algorithm>

#include <Arduino.h>

AudioNode::~AudioNode() {
	for(unsigned int i = 0; i < _node_inputs.size(); i++) {
		_node_inputs[i]->unhook(this);
	}
	_node_inputs.clear();
	_node_outputs.clear();
	_param_inputs.clear();
}

void AudioNode::connect(AudioNode* destination) {
	if(std::find(_node_outputs.begin(), _node_outputs.end(), destination) == _node_outputs.end()) {
		_node_outputs.push_back(destination);
		destination->hook(this);
	}
}

void AudioNode::connect(AudioParamFloat* destination) {
	if(std::find(_param_inputs.begin(), _param_inputs.end(), destination) == _param_inputs.end()) {
		_param_inputs.push_back(destination);
	}
}

void AudioNode::disconnect(AudioNode* destination) {
	_node_outputs.erase(std::remove(_node_outputs.begin(), _node_outputs.end(), destination), _node_outputs.end());
	destination->unhook(this); // no lookup first??
}

void AudioNode::disconnect(AudioParamFloat* destination) {
	_param_inputs.erase(std::remove(_param_inputs.begin(), _param_inputs.end(), destination), _param_inputs.end());
}

int AudioNode::nbr_inputs() {
	return _node_inputs.size();
}

int AudioNode::nbr_outputs() {
	return _node_outputs.size();
}

int AudioNode::nbr_params() {
	return _param_inputs.size();
}

void AudioNode::hook(AudioNode* input) {
	if(std::find(_node_inputs.begin(), _node_inputs.end(), input) == _node_inputs.end()) {
		_node_inputs.push_back(input);
	}
}

void AudioNode::unhook(AudioNode* destination) {
	_node_inputs.erase(std::remove(_node_inputs.begin(), _node_inputs.end(), destination), _node_inputs.end());
}
