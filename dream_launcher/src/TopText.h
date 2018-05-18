#pragma once

#include "ofMain.h"

class TopText {
public:

	void setup(string _message, string fontPath, int fontSize);
	void draw(float centerX, float yPos);

	string message;

	ofTrueTypeFont font;

};
