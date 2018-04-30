#pragma once

#include "ofMain.h"
#include "BounceText.h"

class GameInfo {
public:

	void setup(string title, string byLine, string info, string path);
	void draw(float alpha);


	string titleText;
	string byLineText;
	string infoText;

	ofImage screenshot;
	ofColor testCol;

	string executablePath;

	BounceText * titleFont, * byLineFont, * infoFont;

};
