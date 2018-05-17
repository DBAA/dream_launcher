#include "GameInfo.h"

void GameInfo::setup(string title, string byLine, string info, string path) {
	titleText = title;
	byLineText = byLine;
	infoText = info;
	executablePath = path;
	isWeb = false;
}

void GameInfo::draw(float alpha, int titleColHex, int textColHex, int outlineColHex) {
	float screenshotW = 720;
	float screenshotH = 540;

	//float borderPaddingX = 100;
	float textStartY = ofGetHeight() * textStartYPrc;
	
	float screenShotX = ofGetWidth() * screenshotXPrc;
	float screenShotY = ofGetHeight() * screenshotYPrc;

	float textW = ofGetWidth() * textWPrc;

	//drawing the screenshot
	ofSetColor(255, alpha);
	screenshot.draw(screenShotX, screenShotY, screenshotW, screenshotH);

	//outline
	ofColor outlineCol;
	outlineCol.setHex(outlineColHex);
	outlineCol.a = alpha;
	int outlineSize = 6;
	ofSetColor(outlineCol);
	//top
	ofRect(screenShotX - outlineSize, screenShotY - outlineSize, screenshotW + outlineSize * 2, outlineSize);
	//bottom
	ofRect(screenShotX - outlineSize, screenShotY + screenshotH, screenshotW + outlineSize * 2, outlineSize);
	//left
	ofRect(screenShotX - outlineSize, screenShotY, outlineSize, screenshotH);
	//right
	ofRect(screenShotX + screenshotW, screenShotY, outlineSize, screenshotH);

	
	float textX = ofGetWidth() * textXPrc;

	//title
	ofColor titleCol;
	titleCol.setHex(titleColHex);
	titleCol.a = alpha;
	ofSetColor(titleCol);
	float titleY = textStartY + titleFont->lineHeight;
	float titleHeight = titleFont->draw(titleText, textX, titleY, textW);

	//testing
	//ofNoFill();
	//ofSetColor(255, 0, 0);
	//ofDrawRectangle(textX, titleY, textW, titleHeight);

	//by line
	float byY = titleY + titleHeight + ofGetHeight() * textByLineYSpacingPrc;
	float byLineHeight = byLineFont->draw(byLineText, textX, byY, textW);

	//by info
	ofColor infoCol;
	infoCol.setHex(textColHex);
	infoCol.a = alpha;
	ofSetColor(infoCol);
	float infoY = byY + byLineHeight + ofGetHeight() * textInfoYSpacingPrc;
	infoFont->draw(infoText, textX, infoY, textW);


}