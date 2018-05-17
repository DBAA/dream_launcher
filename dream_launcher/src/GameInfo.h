#pragma once

#include "ofMain.h"
#include "BounceText.h"

class GameInfo {
public:

	void setup(string title, string byLine, string info, string path);
	void draw(float alpha, int titleColHex, int textColHex, int outlineColHex);


	string titleText;
	string byLineText;
	string infoText;

	ofImage screenshot;
	ofColor testCol;

	string executablePath;
	bool isWeb;

	BounceText * titleFont, * byLineFont, * infoFont;

	float infoYPrc;
	float textXPrc, textWPrc;
	float screenshotXPrc;

};
