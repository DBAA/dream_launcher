#include "TopText.h"

void TopText::setup(string _message, string fontPath, int fontSize) {
	message = _message;
	font.load(fontPath, fontSize);
	//font.load("fonts/ChevyRay - Bubble Time.ttf", 60);
	//font.load("fonts/GapSansBold.ttf", 120);
}

void TopText::draw(float centerX, float yPos) {

	float timePerChar = 0.05;
	float timeToDip = 0.15;
	float pauseTime = 3;

	float dipDist = 20;

	float charSpacing = 4;

	float totalTime = timePerChar*message.length() + pauseTime;
	float timer = fmod(ofGetElapsedTimef(), totalTime);

	float textWidth = 0;// font.stringWidth(message) + charSpacing*(message.length() - 1);

	for (int i = 0; i < message.length(); i++) {
		string thisLetter;
		thisLetter.push_back(message[i]);
		textWidth += font.stringWidth(thisLetter) + charSpacing;
		if (thisLetter == " ") {
			textWidth += font.stringWidth("o");
		}

	}


	float curX = 0;

	ofPushMatrix();
	ofTranslate(centerX - textWidth / 2, yPos);

	for (int i = 0; i < message.length(); i++) {
		string thisLetter;
		thisLetter.push_back(message[i]);
		//= "" + message[i];
		float yMod = 0;

		float thisTimer = timer - i*timePerChar;
		if (thisTimer > 0 && thisTimer < timeToDip) {
			float prc = thisTimer / timeToDip;
			yMod = sin(prc * PI) * dipDist;
		}

		font.drawString(thisLetter, curX, yPos + yMod);
		curX += font.stringWidth(thisLetter) + charSpacing;
		if (thisLetter == " ") {
			curX += font.stringWidth("o");
		}

	}


	ofPopMatrix();



}