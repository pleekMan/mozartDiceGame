#pragma once

#include "ofMain.h"
#include "SoundManager.h"


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

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:


};

