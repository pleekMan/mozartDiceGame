#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(true);
	ofBackground(0);
	ofSetFrameRate(30);

	sceneManager.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

	sceneManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// DRAW BACKGROUND LINES
	ofSetColor(255,255,0);
	for (int i = 0; i < ofGetWindowWidth(); i += 40)
	{
		ofLine(i, 0, i, ofGetWindowHeight());
	}

	sceneManager.render();

	ofDrawBitmapString(ofToString(ofGetMouseX()) + " | " + ofToString(ofGetMouseY()), ofGetMouseX() + 10, ofGetMouseY() - 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	sceneManager.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	sceneManager.mouseMoved();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	sceneManager.mouseDragged(button);
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	sceneManager.mousePressed(x, y, button);
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
