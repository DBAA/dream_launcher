#include "GameIcon.h"

void GameIcon::update() {

	animTimer += ofGetLastFrameTime();

	if (animTimer < animEndTime) {
		float prc = animTimer / animEndTime;
		prc = powf(prc, animCurve);
		pos = prc * endPos + (1.0 - prc) * startPos;

	}
	else {
		pos = endPos;
	}

}

void GameIcon::draw() {
	float testW = 400;
	float testH = 200;

	//calculate alpha and scale based on position
	float distFromCenter = abs(ofGetWidth() / 2 - pos.x);
	float prcDistFromCenter = 1.0 - distFromCenter / (float)(ofGetWidth() / 2);
	float alpha = powf(prcDistFromCenter, 0.7) * 255;
	float scale = (1.0f - prcDistFromCenter) * 0.5 + prcDistFromCenter * 1.0;

	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	ofScale(scale, scale);
	ofSetColor(testCol.r, testCol.g, testCol.b, alpha);
	ofDrawRectangle(-testW / 2, -testH / 2, testW, testH);
	ofSetColor(0);
	ofDrawBitmapString(ofToString(idTestNum), 0, 0);
	ofDrawBitmapString(ofToString((int)alpha), 0, 16);
	ofPopMatrix();

}

void GameIcon::startAnimation(float time) {
	animEndTime = time;
	animTimer = 0;
}

/*
void GameIcon::startAnimation(ofVec2f _startPos, ofVec2f _endPos, float time) {
	startPos = _startPos;
	endPos = _endPos;
	animEndTime = time;
	animTimer = 0;

}
*/