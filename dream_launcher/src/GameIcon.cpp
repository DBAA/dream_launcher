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

void GameIcon::draw(int outlineColHex) {
	//float icon_w = 315;
	//float icon_h = 250;

	//calculate alpha and scale based on position
	float distFromCenter = abs(ofGetWidth() / 2 - pos.x);
	float prcDistFromCenter = 1.0 - distFromCenter / (float)(ofGetWidth() / 2);
	float curvePrc = powf(prcDistFromCenter, 0.7);
	float alpha = (1.0f - curvePrc) * 10 + 255 * curvePrc;
	float scale = (1.0f - prcDistFromCenter) * 0.5 + prcDistFromCenter * 1.0;

	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	ofScale(scale, scale);
	ofSetColor(255, alpha);
	iconPic.draw(-icon_w / 2, -icon_h / 2, icon_w, icon_h);

	//outline
	int outlineSize = 3;
	ofColor outlineCol;
	outlineCol.setHex(outlineColHex);
	outlineCol.a = alpha;
	ofSetColor(outlineCol);
	//top
	ofRect(-icon_w / 2 - outlineSize, -icon_h / 2 - outlineSize, icon_w + outlineSize * 2, outlineSize);
	//bottom
	ofRect(-icon_w / 2 - outlineSize, icon_h / 2 , icon_w + outlineSize * 2, outlineSize);
	//left
	ofRect(-icon_w / 2 - outlineSize, -icon_h/2 , outlineSize, icon_h);
	//right
	ofRect(icon_w / 2 , -icon_h / 2, outlineSize, icon_h);


	ofPopMatrix();

}

void GameIcon::startAnimation(float time) {
	animEndTime = time;
	animTimer = 0;
}
