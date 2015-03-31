#pragma once

#include "ofMain.h"
#include "Envelope.h"

class AudioClip: public ofSoundPlayer{

public:

	//AudioClip(Envelope& _envelope);
	AudioClip();

	//Envelope& envelope;
	float crossFade;
	void setVolume(float _volume);
	
};

