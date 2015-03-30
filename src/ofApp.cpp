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
	ofDrawBitmapString("Compas: " + ofToString(soundManager.currentValsCompas + 1) + " of " + ofToString(soundManager.compasesVals.size()), ofPoint(20,20));
	ofDrawBitmapString("Isplaying Vals: " + ofToString(soundManager.isPlayingVals), ofPoint(20, 40));

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1'){
		soundManager.addToVals(soundManager.compases[0]);
	}

	if (key == '2'){
		soundManager.addToVals(soundManager.compases[1]);
	}

	if (key == ' '){
		soundManager.playVals();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
