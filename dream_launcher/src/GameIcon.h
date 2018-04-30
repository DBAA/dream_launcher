#pragma once

#include "ofMain.h"

class GameIcon {
public:

	void update();
	void draw();

	//void startAnimation(ofVec2f _startPos, ofVec2f _endPos, float time);
	void startAnimation(float time);

	ofImage iconPic;

	ofVec2f pos;

	ofColor testCol;

	//animating
	float animTimer;
	float animCurve;
	float animEndTime;

	ofVec2f startPos, endPos;
	//float startScale, targetScale;
	//float startAlpha, targetAlpha;

	//showing the info
	//THIS SHOULD MAYBE BE A DIFFERENT CLASS
	string titleText;
	string byLineText;
	string infoText;

	ofImage screenshot;


	//testing
	int idTestNum;

};
