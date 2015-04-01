#pragma once

#include "ofMain.h"

class CompasButton{

public:
	//CompasButton();

	void setup(float posX, float posY, string imagePath, int _id);
	void update();
	void render();

	int id;
	float x, y, width, height;
	bool active;

	ofImage image;

	void setActive(bool state);
	void toggleActive();
	bool isPointOver(ofPoint);

private:


};

