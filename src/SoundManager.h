//
//  SoundManager.h
//  mozartDiceGame
//
//  Created by PleekMan on 30/3/2015.
//
//

#pragma once

//#ifndef SoundManager
//#define SoundManager

//#include <iostream>

#include "ofMain.h"
//#include "Chain.h"
#include "Envelope.h"
#include "AudioClip.h"

#define COMPAS_COUNT 2

class SoundManager{

public:

	//SoundManager();
	//~SoundManager();

	void setup();
	void update();
	void render();
	
	void loadCompases();
	AudioClip compases [COMPAS_COUNT];
	Envelope envelope;
	float crossFade;

	void playCompas(int compasNumber);
	void addToVals(AudioClip* selectedCompas);
	void playVals();
	void clearVals();

	void drawEnvelopes();

	vector<AudioClip*> compasesVals;
	int currentValsCompas;
	int nextValsCompas;
	bool isPlayingVals;
	bool loop;

	void mouseDragged(int button);

private:

	void updateEnvelope(float attack);
	


};

//#endif /* defined(__CarbonChains__ChainManager__) */