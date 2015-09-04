#pragma once

#include "AudioNode.h"

#include <Arduino.h>


class AudioSourceNode : public virtual AudioNode {
public:
	AudioSourceNode() {}
	inline int nbr_outputs() override { return 0; }

protected:

	inline void hook (AudioNode* input) override {}
	inline void unhook(AudioNode* input) override {}

};
