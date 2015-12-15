#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(true);
	ofBackground(0);
	ofEnableAlphaBlending();
	//ofDisableBlendMode();
	//ofSetFrameRate(10);
	ofHideCursor();
	sceneManager.setup();

	settings.loadFile("settings.xml");
	frameTop = settings.getValue("SETTINGS:frames:top", 50);
	frameBottom = settings.getValue("SETTINGS:frames:bottom", 50);
	frameLeft = settings.getValue("SETTINGS:frames:left", 50);
	frameRight = settings.getValue("SETTINGS:frames:right", 50);

}

//--------------------------------------------------------------
void ofApp::update(){

	sceneManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// DRAW BACKGROUND LINES
	/*
	ofSetColor(255,255,0);
	for (int i = 0; i < ofGetWindowWidth(); i += 40)
	{
		ofLine(i, 0, i, ofGetWindowHeight());
	}
	*/

	sceneManager.render();

	// DRAW BLACK FRAME
	ofPushStyle();
	ofSetColor(0);
	ofFill();

	ofRect(0,0,ofGetScreenWidth(),frameTop); // TOP
	ofRect(0, ofGetScreenHeight() - frameBottom,ofGetScreenWidth(),frameBottom); // BOTTOM
	ofRect(0,0,frameLeft,ofGetScreenHeight()); // LEFT
	ofRect(ofGetScreenWidth() - frameRight,0,frameRight,ofGetScreenHeight()); // RIGHT





	ofPopStyle();

	//ofDrawBitmapString(ofToString(ofGetMouseX()) + " | " + ofToString(ofGetMouseY()), ofGetMouseX() + 10, ofGetMouseY() - 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	sceneManager.keyPressed(key);


	// INCREASE FRAMES
	if (key == OF_KEY_UP)
	{
		frameTop += 2;
		settings.setValue("SETTINGS:frames:top", frameTop);
	}
	if (key == OF_KEY_DOWN)
	{
		frameBottom += 2;
		settings.setValue("SETTINGS:frames:bottom", frameBottom);
	}
	if (key == OF_KEY_LEFT)
	{
		frameLeft += 2;
		settings.setValue("SETTINGS:frames:left", frameLeft);
	}
	if (key == OF_KEY_RIGHT)
	{
		frameRight += 2;
		settings.setValue("SETTINGS:frames:right", frameRight);
	}
	
	// DECREASE FRAMES
	if (key == 'w' || key == 'W')
	{
		frameTop -= 2;
		settings.setValue("SETTINGS:frames:top", frameTop);
	}
	if (key == 's' || key == 'S')
	{
		frameBottom -= 2;
		settings.setValue("SETTINGS:frames:bottom", frameBottom);
	}
	if (key == 'a' || key == 'A')
	{
		frameLeft -= 2;
		settings.setValue("SETTINGS:frames:left", frameLeft);

	}
	if (key == 'd' || key == 'D')
	{
		frameRight -= 2;
		settings.setValue("SETTINGS:frames:right", frameRight);

	}
	settings.saveFile("settings.xml");
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
