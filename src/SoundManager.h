//
//  SoundManager.h
//  mozartDiceGame
//
//  Created by PleekMan on 30/3/2015.
//
//

#pragma once


//#include <iostream>
#include "ofMain.h"

#define COMPAS_COUNT 176
#define SELECTION_COMPASES 16

#include "AudioClip.h"
#include "Envelope.h"

class SoundManager{

public:

	//SoundManager();
	//~SoundManager();

	void setup();
	void reset();
	void update();
	void render();
	
	void loadCompases();

	int userSelection[SELECTION_COMPASES];
	AudioClip compases[COMPAS_COUNT];
	Envelope envelope;
	float crossFade;

	void playCompas(int compasNumber);
	void addToVals(AudioClip* selectedCompas);
	void playVals();
	void clearVals();
	void setCompasSelection(int column, int compas);

	void drawEnvelopes();

	vector<AudioClip*> compasesVals;
	int currentValsCompas;
	int nextValsCompas;
	bool isPlayingVals;
	bool loop;

	void mouseDragged(int button);
	void mouseMoved();

private:

	void updateEnvelope(float attack);
	


};

