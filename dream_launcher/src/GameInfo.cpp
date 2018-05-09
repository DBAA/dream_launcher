#include "GameInfo.h"

void GameInfo::setup(string title, string byLine, string info, string path) {
	titleText = title;
	byLineText = byLine;
	infoText = info;
	executablePath = path;
}

void GameInfo::draw(float alpha) {
	float screenshotW = 720;
	float screenshotH = 540;

	float borderPaddingX = 100;
	float startY = ofGetHeight() * 0.4;

	float screenShotX = ofGetWidth() - screenshotW - borderPaddingX;

	float textW = screenShotX - borderPaddingX * 1;

	//testing until we have screenshots
	ofSetColor(testCol.r, testCol.g, testCol.b, alpha);
	ofFill();
	ofDrawRectangle(screenShotX, startY, screenshotW, screenshotH);

	ofSetColor(0, alpha);

	//title
	float titleY = startY + titleFont->lineHeight + 10;
	titleFont->draw(titleText, borderPaddingX, titleY, textW);

	//by line
	float byY = titleY + titleFont->lineHeight + 80;
	byLineFont->draw(byLineText, borderPaddingX, byY, textW);

	//by info
	float infoY = byY + byLineFont->lineHeight + 60;
	infoFont->draw(infoText, borderPaddingX, infoY, textW);


	ofSetColor(0, alpha);



}