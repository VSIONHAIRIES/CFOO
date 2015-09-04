#pragma once

// http://www.w3.org/TR/webaudio/#AudioNode-section

#include "AudioParam.h"
#include <vector>
#include <stdint.h>

class AudioContext;

class AudioNode {
public:

	AudioNode() {}
	AudioNode(AudioContext* audioContext) : _audioCtx(audioContext) {}
	virtual ~AudioNode();

	virtual void connect(AudioNode* destination);
	virtual void connect(AudioParamFloat* destination);

	virtual void disconnect(AudioNode* destination);
	virtual void disconnect(AudioParamFloat* destination);	

	virtual void process(int64_t& sample) = 0;

	virtual int nbr_inputs(); 
	virtual int nbr_outputs();
	virtual int nbr_params();

	virtual void hook(AudioNode* input);
	virtual void unhook(AudioNode* input);

protected:
	
	AudioContext*	_audioCtx;
	std::vector<AudioNode*> _node_inputs;
	std::vector<AudioNode*> _node_outputs;
	std::vector<AudioParamFloat*> _param_inputs;
};