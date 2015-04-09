#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SoundManager.h"

#define HOST "localhost"
#define SERVER_PORT 10000
#define CLIENT_PORT 10001

enum SceneState{
	SCREENSAVER,
	SELECTION,
	VIDEO_EXPLAIN,
	EXECUTION
};


class SceneManager{

public:
	//SceneManager();

	void setup();
	void update();
	void render();

	SoundManager soundManager;

	ofxOscReceiver netReciever;
	ofxOscSender netSender;

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:

	void checkNetMessages();

};

