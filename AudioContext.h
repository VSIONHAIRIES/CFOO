#pragma once

// http://www.w3.org/TR/webaudio/#AudioContext-section

#include "AudioNode.h"
#include "AudioParam.h"
#include "GainNode.h"
#include "OscillatorNode.h"
#include "AudioDestinationNode.h"
#include "AudioDestinationNode_T3DAC.h"
#include <vector>

class AudioContext {
public:
	AudioContext();
	~AudioContext() {} /// need to finish

	GainNode* createGain();
	OscillatorNode* createOscillator();

	AudioDestinationNode* destination();

	int sample_rate();

private:

	AudioDestinationNode* destination_ptr;

	std::vector<AudioNode*> _nodes;

};