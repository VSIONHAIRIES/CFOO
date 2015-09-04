#pragma once

// http://www.w3.org/TR/webaudio/#GainNode

#include "AudioNode.h"
#include "AudioParam.h"
#include <cstddef>

class GainNode : public AudioNode {

public:

	GainNode(AudioContext* audioContext) : AudioNode(audioContext), _input(NULL), _output(NULL) {}

	void connect(AudioNode* destination) override;
	inline void connect(AudioParamFloat* destination) override {}

	void disconnect(AudioNode* destination) override;
	inline void disconnect(AudioParamFloat* destination) override {}	

	void process(int64_t& sample) override;

	inline int nbr_inputs() override { return 1; }
	inline int nbr_outputs() override {return 1; }
	inline int nbr_params() override {return 0; }


	AudioParam<double>	gain;

protected:

	void hook(AudioNode* input) override;
	void unhook(AudioNode* input) override;


	AudioNode* _input;	//single input
	AudioNode* _output;	//single output
};