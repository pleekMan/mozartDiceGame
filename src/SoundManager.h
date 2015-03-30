//
//  SoundManager.h
//  mozartDiceGame
//
//  Created by PleekMan on 30/3/2015.
//
//

//#ifndef SoundManager
//#define SoundManager

//#include <iostream>

#include "ofMain.h"
//#include "Chain.h"

#define COMPAS_COUNT 2

class SoundManager{

public:
	void setup();
	void update();
	void render();
	
	void loadCompases();
	ofSoundPlayer compases [COMPAS_COUNT];

	void playCompas(int compasNumber);
	void addToVals(ofSoundPlayer selectedCompas);
	void playVals();

	vector<ofSoundPlayer> compasesVals;
	int currentValsCompas;
	int nextValsCompas;
	bool isPlayingVals;

private:

	


};

//#endif /* defined(__CarbonChains__ChainManager__) */