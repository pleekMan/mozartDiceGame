#include "Envelope.h"



Envelope::Envelope()
{

	fadeIn = 0.0182;
	fadeOut = 1.0 - fadeIn;
	maxLevel = 0.8;
}

float Envelope::getLevelAt(float clipPosition){


	float level = 0.0;;
	
	if (clipPosition < fadeIn)
	{
		float reMapPosition = ofMap(clipPosition, 0, fadeIn, 0.0, HALF_PI);
		level = sin(reMapPosition) * maxLevel;
		
	}
	else if(clipPosition > fadeOut){
		
		float reMapPosition = ofMap(clipPosition, fadeOut, 1.0, HALF_PI, PI);
		level = sin(reMapPosition) * maxLevel;
	}
	else {
		level = maxLevel;
	}

	return level;
}

float Envelope::quadInOut(float currentTime, float startValue, float increment, float duration){

	currentTime /= duration / 2;
	if (currentTime < 1) return increment / 2 * currentTime*currentTime + startValue;
	currentTime--;
	return -increment / 2 * (currentTime*(currentTime - 2) - 1) + startValue;

}

float Envelope::quadIn(float currentTime, float startValue, float increment, float duration){

	currentTime /= duration;
	return increment*currentTime*currentTime + startValue;

}

float Envelope::quadOut(float currentTime, float startValue, float increment, float duration){

	currentTime /= 1.0;
	return -increment * currentTime*(currentTime - 2) + 0.0;

}

