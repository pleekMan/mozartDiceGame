#include "Envelope.h"



Envelope::Envelope()
{

	attack = 0.1;
	decay = 1.0 - attack;
}

float Envelope::getLevelAt(float clipPosition){

	//time = clipPosition;

	float level;

	if (clipPosition < attack)
	{
		level = ofMap(clipPosition, 0, Envelope::attack, 0.0, 1.0);
	}
	else {
		level = ofMap(clipPosition, Envelope::decay, 1.0, 1.0, 0.0);
	}

	return ofClamp(level,0.0,1.0);
}

void Envelope::drawEnvelope(){

	ofPoint graphOrigin = ofPoint(300, 300);
	ofPoint graphSize = ofPoint(200, 100);

	ofNoFill();
	ofSetColor(127);
	ofRect(graphOrigin, graphSize.x, graphSize.y);

	ofSetColor(255, 0, 0);
	ofLine(graphOrigin.x, graphOrigin.y + graphSize.y, graphOrigin.x + (graphSize.x * attack), graphOrigin.y);
	ofLine(graphOrigin.x + (graphSize.x * attack), graphOrigin.y, graphOrigin.x + (graphSize.x * decay), graphOrigin.y);
	ofLine(graphOrigin.x + (graphSize.x * decay), graphOrigin.y, graphOrigin.x + graphSize.x, graphOrigin.y + graphSize.y);

	//ofColor(0, 255, 0);
	//ofLine(graphOrigin.x + (graphSize.x * time), graphOrigin.y, graphOrigin.x + (graphSize.x * time), graphOrigin.y - graphSize.y);


}
