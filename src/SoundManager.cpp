#include "SoundManager.h"

void SoundManager::setup(){

	currentValsCompas = 0;
	nextValsCompas = currentValsCompas + 1;
	isPlayingVals = false;
	loop = true;

	crossFade = 0.2;

	loadCompases();
}

void SoundManager::update(){

	// EVERYTHING IS TRIGGERED BY playVals(), WHICH RESETS compasesNumbers AND PLAYS THE FIRST COMPAS
	
	// GLOBAL PLAYING STATE
	if (isPlayingVals){

		// ONLY PLAY WHEN THERE ARE 2 OR MORE COMPASES
		if (compasesVals.size() > 1){
			//cout << " INSIDE VALS" << endl;

			compasesVals[currentValsCompas]->setVolume(envelope.getLevelAt(compasesVals[currentValsCompas]->getPosition()));

			compasesVals[nextValsCompas]->setVolume(envelope.getLevelAt(compasesVals[nextValsCompas]->getPosition()));

			// TRIGGER THE NEXT COMPAS AT CROSSFADE POSITION. UPDATE VARS
			if ((compasesVals[currentValsCompas]->getPosition() + crossFade) > 1.0){

				currentValsCompas = nextValsCompas;
				nextValsCompas = currentValsCompas + 1;
				// IF IN LOOP, AFTER LAST COMPAS, START OVER, ELSE, STOP THE SHIT (LAST COMPAS HAS NO ENVELOPE!!!)
				if (nextValsCompas >= compasesVals.size()){
					if (loop){
						nextValsCompas = 0;
					}
					else {
						isPlayingVals = false;
					}
				}

				compasesVals[currentValsCompas]->play();

			}

		}
	}

}

void SoundManager::render(){
		
	drawEnvelopes();

	ofDrawBitmapString("Current: " + ofToString(currentValsCompas) + " / Next: " + ofToString(nextValsCompas), ofPoint(20, 50));

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

void SoundManager::addToVals(AudioClip* selectedCompas){
	compasesVals.push_back(selectedCompas);
}

void SoundManager::playVals(){

	isPlayingVals = true;

	currentValsCompas = 0;
	nextValsCompas = currentValsCompas + 1;

	compasesVals[currentValsCompas]->play();
}

void SoundManager::clearVals(){
	compasesVals.clear();
	currentValsCompas = 0;
	nextValsCompas = currentValsCompas + 1;
}

void SoundManager::drawEnvelopes(){

	ofPoint graphSize = ofPoint(200, 100);
	ofPoint origin = ofPoint(10, ofGetWindowHeight() * 0.5);

	// GRAPH 1
	ofNoFill();
	ofSetColor(50);
	ofRect(origin, graphSize.x, graphSize.y);

	ofSetColor(0, 255, 0);
	ofLine(origin.x, origin.y + graphSize.y, origin.x + (graphSize.x * envelope.attack), origin.y);
	ofLine(origin.x + (graphSize.x * envelope.attack), origin.y, origin.x + (graphSize.x * envelope.decay), origin.y);
	ofLine(origin.x + (graphSize.x * envelope.decay), origin.y, origin.x + graphSize.x, origin.y + graphSize.y);

	//GRAPH 2

	ofPushMatrix();
	ofTranslate(graphSize.x - (graphSize.x * crossFade), 0.0);

	ofNoFill();
	ofSetColor(50);
	ofRect(origin, graphSize.x, graphSize.y);

	ofSetColor(255, 0, 0);
	ofLine(origin.x, origin.y + graphSize.y, origin.x + (graphSize.x * envelope.attack), origin.y);
	ofLine(origin.x + (graphSize.x * envelope.attack), origin.y, origin.x + (graphSize.x * envelope.decay), origin.y);
	ofLine(origin.x + (graphSize.x * envelope.decay), origin.y, origin.x + graphSize.x, origin.y + graphSize.y);

	ofSetColor(255);
	ofDrawBitmapString("CF: " + ofToString(100.0 * crossFade) + "%", ofPoint(origin.x, origin.y - 20));

	ofPopMatrix();
}

void SoundManager::updateEnvelope(float attack){
	envelope.attack = attack;
	envelope.decay = 1.0 - envelope.attack;
}

void SoundManager::mouseDragged(int button){

	crossFade = ofMap(ofGetMouseX(), 0.0, ofGetWindowWidth(), 0.0, 1.0);
	updateEnvelope(ofMap(ofGetMouseY(), 0.0, ofGetWindowHeight(), 0.0, 1.0));

}

