#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(true);
	ofBackground(0);

	soundManager.setup();


}

//--------------------------------------------------------------
void ofApp::update(){

	soundManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("Compas: " + ofToString(soundManager.currentValsCompas) + " of " + ofToString(soundManager.compasesVals.size() - 1), ofPoint(20,20));
	ofDrawBitmapString("Isplaying Vals: " + ofToString(soundManager.isPlayingVals), ofPoint(20, 40));

	soundManager.render();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	soundManager.mouseMoved();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	soundManager.mouseDragged(button);
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
