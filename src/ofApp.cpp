#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(true);
	ofBackground(0);

	sceneManager.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

	sceneManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	sceneManager.render();

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
