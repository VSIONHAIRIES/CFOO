#pragma once

#include "AudioDestinationNode.h"
#include <stdint.h>

class AudioDestinationNode_T3DAC : public AudioDestinationNode {
public:

	AudioDestinationNode_T3DAC(AudioContext* audioContext);

	void isr(void) override;

	int sample_rate() override; 

private:
	volatile int64_t _sample;
	int64_t _accum;

};

extern AudioDestinationNode_T3DAC t3dac_destinationNode;

