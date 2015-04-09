#include "SceneManager.h"

void SceneManager::setup(){

	netSender.setup(HOST, CLIENT_PORT);
	netReciever.setup(SERVER_PORT);

	soundManager.setup();
}
void SceneManager::update(){

	checkNetMessages();

	soundManager.update();

	
}
void SceneManager::render(){

	ofSetColor(255);
	ofDrawBitmapString("Compas: " + ofToString(soundManager.currentValsCompas) + " of " + ofToString(soundManager.compasesVals.size() - 1), ofPoint(20, 20));
	ofDrawBitmapString("Isplaying Vals: " + ofToString(soundManager.isPlayingVals), ofPoint(20, 40));

	soundManager.render();
}

void SceneManager::checkNetMessages(){

	while (netReciever.hasWaitingMessages()){
		ofxOscMessage m;
		netReciever.getNextMessage(&m);

		// GO TO STATE	
		if (m.getAddress() == "/goToState"){
			cout << "GO TO STATE: " << ofToString(m.getArgAsInt32(0)) << endl;
		}

		// RECIEVE COMPAS SELECTION
		if (m.getAddress() == "/compasSelection"){
			int selection = m.getArgAsInt32(0);

			// 1D to 2D
			int totalColumns = 16;
			int column = selection % totalColumns;
			int row = int(selection / totalColumns);

			soundManager.setCompasSelection(column, row);

			// BROADCAST ACTIVE COLUMN
			ofxOscMessage activeColumnMessage;
			activeColumnMessage.setAddress("/activeColumn");

			if (column == 15){
				activeColumnMessage.addIntArg(-1);
			}
			else {
				activeColumnMessage.addIntArg(column + 1);
			}

			netSender.sendMessage(activeColumnMessage);
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

	if (key == '1'){
		soundManager.addToVals(&soundManager.compases[0]);
	}

	if (key == '2'){
		soundManager.addToVals(&soundManager.compases[1]);
	}

	if (key == ' '){
		soundManager.playVals();
	}

	if (key == 'c'){
		soundManager.clearVals();
	}

	if (key == 's' || key == 'S'){

		ofxOscMessage m;
		m.setAddress("/goToState");
		m.addIntArg(1);
		netSender.sendMessage(m);
	}
}

