#include "SoundManager.h"

void SoundManager::setup(){

	
	loop = false;

	crossFade = 0.67;

	loadCompases();

	reset();

}

void SoundManager::reset(){
	currentValsCompas = 0;
	nextValsCompas = currentValsCompas + 1;
	isPlayingVals = false;
}

void SoundManager::update(){

	// EVERYTHING IS TRIGGERED BY playVals(), WHICH RESETS compasesNumbers AND PLAYS THE FIRST COMPAS
	
	// GLOBAL PLAYING STATE
	if (isPlayingVals){

		// ONLY PLAY WHEN THERE ARE 2 OR MORE COMPASES
		if (compasesVals.size() > 1){
			//cout << " INSIDE VALS" << endl;

			compasesVals[currentValsCompas]->setVolume(envelope.getLevelAt(compasesVals[currentValsCompas]->getPosition()));
			if(nextValsCompas < 16)compasesVals[nextValsCompas]->setVolume(envelope.getLevelAt(compasesVals[nextValsCompas]->getPosition()));

			// TRIGGER THE NEXT COMPAS AT CROSSFADE POSITION. UPDATE VARS
			if ((compasesVals[currentValsCompas]->getPosition() + crossFade) >= 0.99){

				currentValsCompas = nextValsCompas;
				nextValsCompas = currentValsCompas + 1;

				// IF IN LOOP, AFTER LAST COMPAS, START OVER, ELSE, STOP THE SHIT (OOPS! LAST COMPAS HAS NO ENVELOPE!!!)
				if (nextValsCompas > compasesVals.size()){
				//if (nextValsCompas >= 5){ // LESS TIME FOR PRESENTATION
					if (loop){
						nextValsCompas = 0;
					}
					else {
						isPlayingVals = false;
					}
				} else {
					compasesVals[currentValsCompas]->play();
				}
			}
		}
	}

}

void SoundManager::render(){
		
	drawEnvelopes();
	ofDrawBitmapString("Current: " + ofToString(currentValsCompas) + " / Next: " + ofToString(nextValsCompas), ofPoint(20, 50));

	for (int i = 0; i < SELECTION_COMPASES; i++)
	{
		ofNoFill();
		if(i <= currentValsCompas)ofFill();
		ofRect(20 + (20 * i),60,20,20);
	}


}

void SoundManager::loadCompases(){

	cout << "----- LOADING AUDIO FILES --" << endl;

	ofBuffer audioIndex = ofBufferFromFile("grillaMozart.txt", true);

	for (int i = 0; i < COMPAS_COUNT; i++){

		string compasLine = audioIndex.getNextLine();
		string soundPath = "audio/vals/" + compasLine + ".wav";
		compases[i].loadSound(soundPath, false);
		compases[i].setPaused(true);
		cout << ofToString(i) << " > " << compasLine << endl;

	}
	cout << endl;
	cout << "----- DONE! --" << endl;

	// SET UP DEFAULT COMPAS SELECTION (IN CASE NO SELECTION IS TRANSMITTED FROM CLIENTS)
	for (int i = 0; i < SELECTION_COMPASES; i++)
	{
		//addToVals(&compases[int(ofRandom(175))]);
		userSelection[i] = 48 + i;
		addToVals(&compases[userSelection[i]]);

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
	ofFill();
	ofSetColor(255,20);
	ofRect(origin, graphSize.x, graphSize.y);

	ofSetColor(200, 200, 0,255);

	float x, y, xPrev, yPrev;
	xPrev = x = origin.x;
	yPrev = y = origin.y + graphSize.y;

	for (float i = 0.0; i <= 1.0; i += 0.01)
	{
		x = origin.x + (graphSize.x * i);
		y = (origin.y + graphSize.y) - (graphSize.y * envelope.getLevelAt(i));

		ofLine(ofPoint(xPrev, yPrev), ofPoint(x, y));
		//ofEllipse(ofPoint(origin.x + (graphSize.x * i), (origin.y + graphSize.y) - (graphSize.y * envelope.getLevelAt(i))), 3, 3);

		xPrev = x;
		yPrev = y;
	}

	//GRAPH 2

	ofPushMatrix();
	ofTranslate(graphSize.x - (graphSize.x * crossFade), 0.0);

	ofFill();
	ofSetColor(255, 20);
	ofRect(origin, graphSize.x, graphSize.y);

	ofSetColor(200, 200, 0, 255);

	xPrev = x = origin.x;
	yPrev = y = origin.y + graphSize.y;
	for (float i = 0.0; i <= 1.0; i += 0.01)
	{
		x = origin.x + (graphSize.x * i);
		y = (origin.y + graphSize.y) - (graphSize.y * envelope.getLevelAt(i));

		ofLine(ofPoint(xPrev, yPrev), ofPoint(x, y));
		//ofEllipse(ofPoint(origin.x + (graphSize.x * i), (origin.y + graphSize.y) - (graphSize.y * envelope.getLevelAt(i))), 3, 3);

		xPrev = x;
		yPrev = y;
	}

	ofPopMatrix();


	ofDrawBitmapString("CF: " + ofToString(crossFade) + " | Sine Fade: " + ofToString(envelope.fadeIn), ofPoint(20, 100));

}
	
void SoundManager::updateEnvelope(float attack){
	envelope.fadeIn = attack;
	envelope.fadeOut = 1.0 - envelope.fadeIn;
}

void SoundManager::setCompasSelection(int column, int compas){
	
	userSelection[column] = compas;

	if (column == 15){
	//if (column == 7){ // PARA TESTEAR LA PRIMER PANTALLA NOMAS
		compasesVals.clear();
		for (int i = 0; i < SELECTION_COMPASES; i++)
		{
			//addToVals(&compases[int(ofRandom(175))]);
			addToVals(&compases[userSelection[i]]);

		}
	}
	cout << "Selected Compas: " << ofToString(column) << " -  " << ofToString(compas) << endl;

}

void SoundManager::mouseDragged(int button){

	envelope.maxLevel = 1 - (float(ofGetMouseY()) / float(ofGetWindowHeight()));

}

void SoundManager::mouseMoved(){
	//crossFade = ofMap(ofGetMouseX(), 0.0, ofGetWindowWidth(), 0.0, 1.0);
	//updateEnvelope(ofMap(ofGetMouseY(), 0.0, ofGetWindowHeight(), 0.0, 0.5));
}

