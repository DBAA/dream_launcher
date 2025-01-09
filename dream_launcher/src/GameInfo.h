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

	float textStartYPrc;
	float textXPrc, textWPrc;
	float textByLineYSpacingPrc;
	float textInfoYSpacingPrc;
	
	float screenshotW;
	float screenshotXPrc;
	float screenshotYPrc;

	bool is_general_info;
	bool show_image_for_general_info;

};
