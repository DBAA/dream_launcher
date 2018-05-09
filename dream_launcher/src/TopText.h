#pragma once

#include "ofMain.h"

class TopText {
public:

	void setup(string _message);
	void draw(float centerX, float yPos);

	string message;

	ofTrueTypeFont font;

};
