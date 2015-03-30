#include "SoundManager.h"

void SoundManager::setup(){

	loadCompases();
	currentValsCompas = 0;
	nextValsCompas = currentValsCompas + 1;
	isPlayingVals = false;
}

void SoundManager::update(){

	if (isPlayingVals){

		if (currentValsCompas < compasesVals.size() - 1){

			//cout << " INSIDE VALS" << endl;
			//compasesVals[currentValsCompas].play();

			if (!compasesVals[currentValsCompas].getIsPlaying()){
				compasesVals[nextValsCompas].play();

				currentValsCompas = nextValsCompas;
				nextValsCompas = currentValsCompas + 1;
			}

			//if (currentValsCompas >= compasesVals.size() - 2){
				//isPlayingVals == false;
			//}
		}
		else {
			isPlayingVals = false;
			//cout << " OUTSIDE VALS" << endl;

		}
	}

}

void SoundManager::loadCompases(){

	for (int i = 0; i < COMPAS_COUNT; i++){
		string soundPath = "audio/" + ofToString(i) + ".mp3";
		compases[i].loadSound(soundPath, false);
		compases[i].setPaused(true);
	}

}

void SoundManager::playCompas(int compasNumber){

	compases[compasNumber].setPaused(false);
	compases[compasNumber].play();
}

void SoundManager::addToVals(ofSoundPlayer selectedCompas){
	compasesVals.push_back(selectedCompas);
}

void SoundManager::playVals(){

	isPlayingVals = true;

	currentValsCompas = 0;
	nextValsCompas = currentValsCompas + 1;

	compasesVals[currentValsCompas].play();
}
