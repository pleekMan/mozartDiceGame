#include "CompasButton.h"

void CompasButton::setup(float posX, float posY, string imagePath, int _id){

	id = _id;

	x = posX;
	y = posY;
	//image.loadImage("images/buttons/button" + ofToString)
	image.loadImage(imagePath);

	if (image.isAllocated())
	{
		width = image.width;
		height = image.height;
	}
	else {
		width = 50;
		height = 30;
	}


}
void CompasButton::update(){

}
void CompasButton::render(){

	ofNoFill();
	ofRect(x, y, width, height);
}

void CompasButton::setActive(bool state){
	active = state;
}

void CompasButton::toggleActive(){
	active = !active;
}

bool CompasButton::isPointOver(ofPoint point){
	ofRectangle buttonArea;
	buttonArea.set(x, y, width, height);

	if (buttonArea.inside(point))
	{
		return true;
	}
	else{
		return false;
	}
}

