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
	float attack, decay;

	float getLevelAt(float clipPosition);

	void drawEnvelope();

private:



};

