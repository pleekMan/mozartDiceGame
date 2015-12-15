#include "SceneManager.h"

void SceneManager::setup(){

	// LOAD SETTINGS -------------- BEGIN

	if (settings.loadFile("settings.xml"))
	{
		string networkBroadCastIP = settings.getValue("SETTINGS:broadCastIP", "192.168.1.255", 0);
		int serverPort = settings.getValue("SETTINGS:servertPort", 12000, 0);
		int clientsPort = settings.getValue("SETTINGS:clientPort", 12001, 0);

		netSender.setup(networkBroadCastIP, clientsPort); // (SEARCH TAG, DEFAULT, ARGUMENT NUMBER)
		netReciever.setup(serverPort);
	}
	else {

		netSender.setup("localhost", 12001);
		//netSender.setup("192.168.1.255", 12001); // (SEARCH TAG, DEFAULT, ARGUMENT NUMBER)
		netReciever.setup(12000);

		cout << "--------- SETTINGS FILE NOT LOADED, DEFAULTING: SENDER IP: LOCALHOST - 12001 " << endl;
	}
	// LOAD SETTINGS -------------- END

	/*
	diceProbabilities[0] = 0.0277;
	diceProbabilities[1] = 0.0554;
	diceProbabilities[2] = 0.0831;
	diceProbabilities[3] = 0.1108;
	diceProbabilities[4] = 0.1385;
	diceProbabilities[5] = 0.1662;
	//diceProbabilities[5] = 2.0;
	diceProbabilities[6] = 0.1385;
	diceProbabilities[7] = 0.1108;
	diceProbabilities[8] = 0.0831;
	diceProbabilities[9] = 0.0554;
	diceProbabilities[10] = 0.0277;
	*/

	// SET LAYERS
	for (int i = 0; i < 4; i++)
	{
		stateLayers[i].allocate(ofGetWindowWidth(), ofGetWindowHeight());
		stateLayers[i].begin();
		ofClear(0);
		stateLayers[i].end();
	}

	layerTransition.setDuration(1.0);
	layerTransition.setPercentDone(0.0);
	layerTransition.reset(0.0);
	layerTransition.setCurve(EASE_IN_EASE_OUT);


	// SET VIDEOS
	videos[0].loadMovie("video/1 - SCREENSAVER.mov");
	videos[1].loadMovie("video/2 - SELECCION.mov");
	videos[2].loadMovie("video/3 - ANIMACION.mov");
	videos[3].loadMovie("video/4 - EJECUCION.mov");

	videos[SCREENSAVER].setLoopState(OF_LOOP_NORMAL);
	videos[SELECTION].setLoopState(OF_LOOP_NORMAL);
	videos[VIDEO_EXPLAIN].setLoopState(OF_LOOP_NONE);
	videos[EXECUTION].setLoopState(OF_LOOP_NORMAL);

	videos[SCREENSAVER].play();
	videos[SELECTION].play();
	videos[VIDEO_EXPLAIN].play();
	videos[EXECUTION].play();

	videos[SCREENSAVER].setPaused(true);
	videos[SELECTION].setPaused(true);
	videos[VIDEO_EXPLAIN].setPaused(true);
	videos[EXECUTION].setPaused(true);
	
	/*
	for (int i = 0; i < 4; i++){
		noteBursts[i].setPixelFormat(OF_PIXELS_RGBA); // WINDOWS NEEDS THIS TO RENDER WITH ALPHA CHANNEL (with PATCHED ofVideoShits cpp an h)
		noteBursts[i].loadMovie("video/BURSTS_" + ofToString(i) + ".mov");
		noteBursts[i].setLoopState(OF_LOOP_NONE);
		noteBursts[i].play();
		noteBursts[i].setPaused(true);
	}
	*/
	fondoNotesCounter = 0;

	//componiendo.loadImage("images/componiendo.png");

	diceRollSound.loadSound("audio/diceRoll_0.mp3");
	diceRollSound2.loadSound("audio/diceRoll_1.mp3");

	for (int i = 0; i < 3; i++){
		cuerdasFondo[i].loadSound("audio/cuerdas_" + ofToString(i) + ".wav");
		cuerdasFondo[i].setVolume(0.2);
	}


	soundManager.setup();

	setState(SCREENSAVER);
	clientsFinishedSelecting[0] = false;
	clientsFinishedSelecting[1] = false;

	enableRestart = false;
	showDebugSound = false;

}
void SceneManager::update(){

	checkNetMessages();

	layerTransition.update(1.0 / ofGetFrameRate());

	// RENDER ONLY ACTUAL AND PREVIOUS LAYERS (UNTIL TRANSITION IS FINISHED) (NOT STOPPING VIDEO)
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);


	if (sceneState == SCREENSAVER || (prevSceneState == SCREENSAVER && layerTransition.isAnimating())){
		stateLayers[SCREENSAVER].begin();
		ofBackground(0);
		videos[SCREENSAVER].update();
		videos[SCREENSAVER].draw(0, 0, stateLayers[SCREENSAVER].getWidth(), stateLayers[SCREENSAVER].getHeight());
		stateLayers[SCREENSAVER].end();
	}

	if (sceneState == SELECTION || (prevSceneState == SELECTION && layerTransition.isAnimating())){
		stateLayers[SELECTION].begin();
		ofBackground(0);
		videos[SELECTION].update();
		videos[SELECTION].draw(0, 0, stateLayers[SELECTION].getWidth(), stateLayers[SELECTION].getHeight());
		stateLayers[SELECTION].end();

		if(!diceRollSound.getIsPlaying() && !diceRollSound2.getIsPlaying() && ofRandom(1.0) < 0.005){
			if(ofRandom(1.0) < 0.5){
				diceRollSound.play();
			} else {
				diceRollSound2.play();
			}
		}

		if(!cuerdasFondo[0].getIsPlaying() && !cuerdasFondo[1].getIsPlaying() && !cuerdasFondo[2].getIsPlaying()){
			float randomSelect = ofRandom(1.0);
			if(randomSelect < 0.33){
				cuerdasFondo[0].play();
			} else if(randomSelect < 0.66){
				cuerdasFondo[1].play();
			}
			else {
				cuerdasFondo[2].play();
			}
		}

		if (clientsFinishedSelecting[0] && clientsFinishedSelecting[1])
		{
			//finalProbability =  calculateProbability();

			setState(VIDEO_EXPLAIN);
			clientsFinishedSelecting[1] = clientsFinishedSelecting[0] = false;

			// SEND CALCULATED PROBABILITY FOR USER SELECTION
			/*
			ofxOscMessage mProb;
			mProb.setAddress("/probability");
			mProb.addIntArg(finalProbability);
			netSender.sendMessage(mProb);
			*/

			// SEND STATE CHANGE
			ofxOscMessage m;
			m.setAddress("/goToState");
			m.addIntArg(VIDEO_EXPLAIN);
			netSender.sendMessage(m);

		}

	}
	if (sceneState == VIDEO_EXPLAIN || (prevSceneState == VIDEO_EXPLAIN && layerTransition.isAnimating())){
		stateLayers[VIDEO_EXPLAIN].begin();
		ofBackground(0);

		videos[VIDEO_EXPLAIN].update();
		videos[VIDEO_EXPLAIN].draw(0, 0, stateLayers[VIDEO_EXPLAIN].getWidth(), stateLayers[VIDEO_EXPLAIN].getHeight());

		if (videos[VIDEO_EXPLAIN].getIsMovieDone() && sceneState == VIDEO_EXPLAIN){
			videos[VIDEO_EXPLAIN].setPaused(true);
			setState(EXECUTION);

			ofxOscMessage m;
			m.setAddress("/goToState");
			m.addIntArg(EXECUTION);
			netSender.sendMessage(m);
		}

		//componiendo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

		stateLayers[VIDEO_EXPLAIN].end();

	}

	if (sceneState == EXECUTION || (prevSceneState == EXECUTION && layerTransition.isAnimating())){
		stateLayers[EXECUTION].begin();
		ofBackground(0);

		videos[EXECUTION].update();
		videos[EXECUTION].draw(0, 0, stateLayers[EXECUTION].getWidth(), stateLayers[EXECUTION].getHeight());

		//ofEnableBlendMode(OF_BLENDMODE_ADD);
		//noteBursts[fondoNotesCounter].update();
		//noteBursts[fondoNotesCounter].draw(0, 0, stateLayers[EXECUTION].getWidth(), stateLayers[EXECUTION].getHeight());
		//ofDisableBlendMode();

		soundManager.update();
		if(showDebugSound)soundManager.render();

		if(!soundManager.isPlayingVals && !enableRestart){
			ofxOscMessage mR;
			mR.setAddress("/enableRestart");
			netSender.sendMessage(mR);
			enableRestart = true;
		}


		stateLayers[EXECUTION].end();
	}





}
void SceneManager::render(){

	//ofSetColor(255, 255.0 * (ofGetMouseX() / float(ofGetWindowWidth())));

	/*
	ofSetColor(255);
	stateLayers[prevSceneState].draw(0, ofGetWindowHeight() * 0.5, ofGetWindowWidth(), ofGetWindowHeight() * 0.5);
	ofSetColor(255,255.0 * layerTransition.getCurrentValue());
	stateLayers[sceneState].draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() * 0.5);
	*/

	ofSetColor(255);
	stateLayers[prevSceneState].draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	ofSetColor(255, 255.0 * layerTransition.getCurrentValue());
	stateLayers[sceneState].draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	ofSetColor(255);
	//ofDrawBitmapString("Compas: " + ofToString(soundManager.currentValsCompas) + " of " + ofToString(soundManager.compasesVals.size() - 1), ofPoint(20, 20));
	//ofDrawBitmapString("Isplaying Vals: " + ofToString(soundManager.isPlayingVals), ofPoint(20, 40));


}

void SceneManager::checkNetMessages(){

	while (netReciever.hasWaitingMessages()){
		ofxOscMessage m;
		netReciever.getNextMessage(&m);

		cout << "MSG RECEIVED -> ADDRESS: " << m.getAddress() << endl;

		// RECIEVE AND BROADCAST -> START GAME
		if (m.getAddress() == "/start"){
			setState(SELECTION);

			ofxOscMessage reSendState;
			reSendState.setAddress("/goToState");
			reSendState.addIntArg(SELECTION);
			netSender.sendMessage(reSendState);
		}

		// RECIEVE -> GO TO STATE	
		if (m.getAddress() == "/goToState"){
			cout << "GO TO STATE: " << ofToString(m.getArgAsInt32(0)) << endl;
			int nextState = m.getArgAsInt32(0);
			setState(nextState);

			ofxOscMessage reSendState;
			reSendState.setAddress("/goToState");
			reSendState.addIntArg(nextState);
			netSender.sendMessage(reSendState);
		}


		// RECIEVE -> COMPAS SELECTION -> SAVE COMPAS SELECTION TO SoundManager
		if (m.getAddress() == "/compasSelection"){

			int fromClient = m.getArgAsInt32(0);
			int serverGridColumnCount = SELECTION_COMPASES;


			// ADAPT GRIDS FROM CLIENTS (HALF A GRID) TO THE SERVERS COMPLETE GRID OF COMPASES
			for (int i = 0; i < 8; i++)
			{
				int clientGridSelection = m.getArgAsInt32(i + 1); // FIRST ARGUMENT IN MESSAGE IS clientID
				int clientRow = int(clientGridSelection / (SELECTION_COMPASES / 2));

				if (fromClient == 0)
				{
					int serverGridSelection = clientGridSelection + (clientRow * (serverGridColumnCount / 2)); // userSelection + (userRow * (serverColumnWidth / 2))
					soundManager.setCompasSelection(i, serverGridSelection);
					//cout << "SELECTED COMPAS: " + ofToString(serverGridSelection) << endl;
					clientsFinishedSelecting[0] = true;
					
				}
				else {
					int serverGridSelection = clientGridSelection + ((serverGridColumnCount / 2) * (clientRow + 1)); // userSelection + ( (userRow + 1) * (serverColumnWidth / 2))
					soundManager.setCompasSelection(i+8, serverGridSelection);
					clientsFinishedSelecting[1] = true;
				}

				cout << "Column: " << ofToString(i) << " / Compas: " << ofToString(soundManager.userSelection[i]) << endl;
			}

			// UNLOCK 2nd SCREEN
			if (fromClient == 0){
				ofxOscMessage unlockScreen;
				unlockScreen.setAddress("/unlockScreen");
				netSender.sendMessage(unlockScreen);
			}
			/*
			else {
			ofxOscMessage gridMessage;
			gridMessage.setAddress("/goToState");
			gridMessage.addIntArg(VIDEO_EXPLAIN);
			setState(VIDEO_EXPLAIN);
			netSender.sendMessage(gridMessage);
			}
			*/


			/*
			// 1D to 2D
			int totalColumns = SELECTION_COMPASES;
			int column = selection % totalColumns;
			int row = int(selection / totalColumns);

			soundManager.setCompasSelection(column, row);

			// BROADCAST ACTIVE COLUMN
			ofxOscMessage gridMessage;
			if (column != 15){
			// IF NOT FINISHED SELECTING -> NEXT COLUMN
			gridMessage.setAddress("/activeColumn");
			gridMessage.addIntArg(column + 1);
			}
			else {
			// IF FINISHED SELECTING -> GOT TO STATE 2
			gridMessage.setAddress("/goToState");
			gridMessage.addIntArg(VIDEO_EXPLAIN);
			setState(VIDEO_EXPLAIN);
			}
			netSender.sendMessage(gridMessage);
			*/

		}
	}


}

void SceneManager::setState(int state){
	sceneState = state;
	prevSceneState = sceneState == 0 ? 3 : sceneState - 1;


	layerTransition.setPercentDone(0.0);
	layerTransition.reset(0.0);
	layerTransition.animateTo(1.0);

	if (sceneState == SCREENSAVER)
	{
		//noteBursts[fondoNotesCounter].setPaused(true);

		videos[SCREENSAVER].setFrame(0);
		videos[SCREENSAVER].setPaused(false);
		//videos[EXECUTION].setFrame(0);
		//videos[EXECUTION].setPaused(true);

		soundManager.isPlayingVals = false;

	}

	else if (sceneState == SELECTION)
	{
		videos[SELECTION].setFrame(0);
		videos[SELECTION].setPaused(false);
		//videos[SCREENSAVER].setFrame(0);
		//videos[SCREENSAVER].setPaused(true);

		clientsFinishedSelecting[0] = true;
		clientsFinishedSelecting[1] = false;

		diceRollSound.setPaused(true);
		diceRollSound2.setPaused(true);

	}

	else if (sceneState == VIDEO_EXPLAIN)
	{
		videos[VIDEO_EXPLAIN].setFrame(0);
		videos[VIDEO_EXPLAIN].setPaused(false);

		diceRollSound.setPaused(true);
		diceRollSound2.setPaused(true);
		cuerdasFondo[0].setPaused(true);
		cuerdasFondo[1].setPaused(true);
		cuerdasFondo[2].setPaused(true);

		//videos[SELECTION].setFrame(0);
		//videos[SELECTION].setPaused(true);


		/*
		for (int i = 0; i < 3; i++){
		cuerdasFondo[i].setPaused(true);
		}
		*/
	}

	else if (sceneState == EXECUTION)
	{
		videos[EXECUTION].setFrame(0);
		videos[EXECUTION].play();
		

		/*
		for (int i = 0; i < 16; i++)
		{
			cout << " - " << ofToString(soundManager.userSelection[i]);
		}
		cout << endl;
		*/

		soundManager.playVals();

		fondoNotesCounter = (fondoNotesCounter + 1) % 4;
		cout << ofToString(fondoNotesCounter) << endl;
		//noteBursts[fondoNotesCounter].setFrame(0);
		//noteBursts[fondoNotesCounter].setPaused(false);

		enableRestart = false;

		//videos[VIDEO_EXPLAIN].setFrame(0);
		//videos[VIDEO_EXPLAIN].setPaused(true);
	}

	/*
	ofxOscMessage m;
	m.setAddress("/goToState");
	m.addIntArg(sceneState);
	netSender.sendMessage(m);
	*/


}

int SceneManager::calculateProbability(){
	double prob = 1.0;

	for (int i = 0; i < 16; i++) 
	{
		int selectedRowInColumn = floor(soundManager.userSelection[i] / 16.0);
		//prob *= diceProbabilities[selectedRowInColumn];
		cout << ofToString(i) << ":: Row:" << ofToString(selectedRowInColumn) <<  " - Prob:" << ofToString(prob) << endl;
	}
	cout <<":: Prob Final:" << ofToString(prob) << endl;

	//double totalValsEver = 45949729863572161;
	double totalValsEver = 1045949729863572161;
	cout <<":: Prob Final int:" << ofToString(int(prob*totalValsEver)) << endl;

	return int(totalValsEver * prob);
}


void SceneManager::mousePressed(int x, int y, int button){

	if (sceneState == SCREENSAVER)
	{
		ofRectangle buttonArea = ofRectangle(ofPoint(100, 100), 300, 100);
		if (buttonArea.inside(x,y))
		{
			setState(SELECTION);

		}
	}
}

void SceneManager::mouseDragged(int button){
	soundManager.mouseDragged(button);


}

void SceneManager::mouseMoved(){
	soundManager.mouseMoved();
}

void SceneManager::keyPressed(int key){

	if (key == '0'){
		//soundManager.addToVals(&soundManager.compases[0]);
		setState(SCREENSAVER);

		ofxOscMessage sendState;
		sendState.setAddress("/goToState");
		sendState.addIntArg(SCREENSAVER);
		netSender.sendMessage(sendState);
	}

	if (key == '1'){
		//soundManager.addToVals(&soundManager.compases[1]);
		setState(SELECTION);
	}
	if (key == '2'){
		setState(VIDEO_EXPLAIN);
	}
	if (key == '3'){
		setState(EXECUTION);
	}

	if (key == ' '){
		//soundManager.playVals();
	}

	/*
	if (key == 'z' || key == 'Z'){
		clientsFinishedSelecting[0] = true;
		clientsFinishedSelecting[1] = true;
	}

	
	if (key == 's' || key == 'S'){

		ofxOscMessage m;
		m.setAddress("/unlockScreen");
		netSender.sendMessage(m);
	}

	if (key == 'd' || key == 'D'){
		showDebugSound = !showDebugSound;
	}
	*/
}

