#pragma once

#include "ofMain.h"

class BounceText {
public:

	void setup(string fontPath, int _fontSize);
	void draw(string textToDraw, int _x, int _y, int textWidth);
	void drawLine(string lineText, int _x, int _y, int charStartNum);


	ofTrueTypeFont font;
	float fontSize;
	float waveSpeed, waveStep, waveSize;

	int spaceWidth;
	int lineHeight;
	int charSpacing;

};
