#pragma once

#include "ofMain.h"



class AudioClip: public ofSoundPlayer{

public:

	AudioClip();

	virtual void setVolume(float _volume);
	
};
