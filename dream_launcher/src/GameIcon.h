#pragma once

#include "ofMain.h"

class GameIcon {
public:

	void update();
	void draw(int outlineColHex);

	void startAnimation(float time);

	ofImage iconPic;

	ofVec2f pos;

	//ofColor testCol;

	//animating
	float animTimer;
	float animCurve;
	float animEndTime;

	ofVec2f startPos, endPos;

	//testing
	int idTestNum;

};
