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

#define COMPAS_COUNT 2

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

	int userSelection[16];
	AudioClip compases[2];
	Envelope envelope;
	float crossFade;

	void playCompas(int compasNumber);
	void addToVals(AudioClip* selectedCompas);
	void playVals();
	void clearVals();
	void setCompasSelection(int column, int row);

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

