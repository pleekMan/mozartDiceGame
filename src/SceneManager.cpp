#include "SceneManager.h"

void SceneManager::setup(){



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
	layerTransition.setCurve(AnimCurve::EASE_IN_EASE_OUT);


	// SET VIDEOS
	videos[0].loadMovie("video/1 - SCREENSAVER.mp4");
	videos[1].loadMovie("video/2 - SELECCION.mov");
	videos[2].loadMovie("video/3 - ANIMACION.mov");
	videos[3].loadMovie("video/4 - EJECUCION.mov");

	videos[SCREENSAVER].setLoopState(OF_LOOP_NORMAL);
	videos[SELECTION].setLoopState(OF_LOOP_NORMAL);
	videos[VIDEO_EXPLAIN].setLoopState(OF_LOOP_NORMAL);
	videos[EXECUTION].setLoopState(OF_LOOP_NORMAL);

	videos[SCREENSAVER].setPaused(true);
	videos[SELECTION].setPaused(true);
	videos[VIDEO_EXPLAIN].setPaused(true);
	videos[EXECUTION].setPaused(true);

	componiendo.loadImage("images/componiendo.png");
	

	netSender.setup(HOST, CLIENT_PORT);
	netReciever.setup(SERVER_PORT);

	soundManager.setup();

	setState(SCREENSAVER);
	clientsFinishedSelecting[0] = false;
	clientsFinishedSelecting[1] = true;

}
void SceneManager::update(){

	checkNetMessages();

	layerTransition.update(1.0 / ofGetFrameRate());


	// RENDER ONLY ACTUAL AND PREVIOUS LAYERS (UNTIL TRANSITION IS FINISHED) (NOT STOPPING VIDEO)
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

		if (clientsFinishedSelecting[0] && clientsFinishedSelecting[1])
		{
			setState(VIDEO_EXPLAIN);
		}

	}
	if (sceneState == VIDEO_EXPLAIN || (prevSceneState == VIDEO_EXPLAIN && layerTransition.isAnimating())){
		stateLayers[VIDEO_EXPLAIN].begin();
		ofBackground(0);
		videos[VIDEO_EXPLAIN].update();
		videos[VIDEO_EXPLAIN].draw(0, 0, stateLayers[VIDEO_EXPLAIN].getWidth(), stateLayers[VIDEO_EXPLAIN].getHeight());

		componiendo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

		stateLayers[VIDEO_EXPLAIN].end();

	}
	
	if (sceneState == EXECUTION || (prevSceneState == EXECUTION && layerTransition.isAnimating())){
		stateLayers[EXECUTION].begin();
		ofBackground(0);

		videos[EXECUTION].update();
		videos[EXECUTION].draw(0, 0, stateLayers[EXECUTION].getWidth(), stateLayers[EXECUTION].getHeight());

		soundManager.update();
		soundManager.render();


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

		cout << "RECIEVED MESSAGE WITH ADDRESS: " << m.getAddress() << endl;

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
					clientsFinishedSelecting[0] = true;
				}
				else {
					int serverGridSelection = clientGridSelection + ((serverGridColumnCount / 2) * (clientRow + 1)); // userSelection + ( (userRow + 1) * (serverColumnWidth / 2))
					soundManager.setCompasSelection(i+8, serverGridSelection);
					clientsFinishedSelecting[1] = true;
				}

				//cout << "Column: " << ofToString(i) << " / Compas: " << ofToString(soundManager.userSelection[i]) << endl;
			}
			
			
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
		videos[SCREENSAVER].play();
		//videos[EXECUTION].setFrame(0);
		//videos[EXECUTION].setPaused(true);

		soundManager.isPlayingVals = false;
		
	}

	else if (sceneState == SELECTION)
	{
		videos[SELECTION].play();

		clientsFinishedSelecting[0] = false;
		clientsFinishedSelecting[1] = true;

		//videos[SCREENSAVER].setFrame(0);
		//videos[SCREENSAVER].setPaused(true);
		
	}

	else if (sceneState == VIDEO_EXPLAIN)
	{
		videos[VIDEO_EXPLAIN].play();
		//videos[SELECTION].setFrame(0);
		//videos[SELECTION].setPaused(true);
	}

	else if (sceneState == EXECUTION)
	{
		videos[EXECUTION].play();
		
		soundManager.playVals();
			
		//videos[VIDEO_EXPLAIN].setFrame(0);
		//videos[VIDEO_EXPLAIN].setPaused(true);
	}

	ofxOscMessage m;
	m.setAddress("/goToState");
	m.addIntArg(sceneState);
	netSender.sendMessage(m);
	

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

	if (key == 'c'){
		//soundManager.clearVals();
	}

	if (key == 's' || key == 'S'){

		ofxOscMessage m;
		m.setAddress("/goToState");
		m.addIntArg(1);
		netSender.sendMessage(m);
	}
}

