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
	float curvePrc = powf(prcDistFromCenter, 0.7);
	float alpha = (1.0f - curvePrc) * 50 + 255 * curvePrc;
	float scale = (1.0f - prcDistFromCenter) * 0.5 + prcDistFromCenter * 1.0;

	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	ofScale(scale, scale);
	ofSetColor(255, alpha);
	iconPic.draw(-testW / 2, -testH / 2, testW, testH);

	//outline
	int outlineSize = 3;
	ofSetColor(0, alpha);
	//top
	ofRect(-testW / 2 - outlineSize, -testH / 2 - outlineSize, testW + outlineSize * 2, outlineSize);
	//bottom
	ofRect(-testW / 2 - outlineSize, testH / 2 , testW + outlineSize * 2, outlineSize);
	//left
	ofRect(-testW / 2 - outlineSize, -testH/2 , outlineSize, testH);
	//right
	ofRect(testW / 2 , -testH / 2, outlineSize, testH);


	ofPopMatrix();

}

void GameIcon::startAnimation(float time) {
	animEndTime = time;
	animTimer = 0;
}
