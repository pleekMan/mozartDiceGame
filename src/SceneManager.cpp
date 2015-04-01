#include "SceneManager.h"

void SceneManager::setup(){
	soundManager.setup();
}
void SceneManager::update(){
	soundManager.update();
}
void SceneManager::render(){

	ofSetColor(255);
	ofDrawBitmapString("Compas: " + ofToString(soundManager.currentValsCompas) + " of " + ofToString(soundManager.compasesVals.size() - 1), ofPoint(20, 20));
	ofDrawBitmapString("Isplaying Vals: " + ofToString(soundManager.isPlayingVals), ofPoint(20, 40));

	soundManager.render();
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
}

