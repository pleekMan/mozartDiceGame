#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SoundManager.h"
#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"

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

	int sceneState;
	int prevSceneState;
	ofFbo stateLayers[4];

	ofxAnimatableFloat layerTransition;
	ofVideoPlayer videos[4];
	//ofImage images[4];

	void setState(int state);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:

	void checkNetMessages();

};

