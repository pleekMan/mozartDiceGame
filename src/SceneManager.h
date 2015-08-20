#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SoundManager.h"
#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxXMLSettings.h"

/*
//#define LOCALHOST_NETWORK_CONFIG

#ifdef LOCALHOST_NETWORK_CONFIG
#define HOST "localhost"
#else
#define HOST "192.168.1.20" 
#endif

#define SERVER_PORT 12000
#define CLIENT_PORT 12001
*/

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

	ofxXmlSettings settings;

	SoundManager soundManager;

	ofxOscReceiver netReciever;
	ofxOscSender netSender;

	bool clientsFinishedSelecting[2];
	bool enableRestart;
	bool showDebugSound;

	//int finalProbability;
	//float diceProbabilities [11]; // PROBABILITIES FOR EACH DICE PAIR/ROW

	int sceneState;
	int prevSceneState;
	ofFbo stateLayers[4];

	ofxAnimatableFloat layerTransition;
	ofVideoPlayer videos[4];
	//ofImage componiendo;
	//ofImage images[4];
	//ofVideoPlayer noteBursts [4];
	int fondoNotesCounter;

	ofSoundPlayer diceRollSound;
	ofSoundPlayer diceRollSound2;
	ofSoundPlayer cuerdasFondo[3];

	void setState(int state);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:

	void checkNetMessages();
	int calculateProbability();

};

