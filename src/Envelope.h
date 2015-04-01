#pragma once

#include "ofMain.h"
#include "ofxAnimatable.h"

class Envelope
{
public:
	Envelope();
	//~Envelope();

	//static float level;
	//float time;
	float fadeIn, fadeOut;
	float maxLevel;
	float getLevelAt(float clipPosition);


private:
	//NOT USED. USING A SIMPLE SINE MAPPING
	float quadInOut(float currentTime, float startValue, float increment, float duration);
	float quadIn(float currentTime, float startValue, float increment, float duration);
	float quadOut(float currentTime, float startValue, float increment, float duration);


};

