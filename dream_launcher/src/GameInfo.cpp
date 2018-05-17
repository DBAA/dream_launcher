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
	float startY = ofGetHeight() * infoYPrc;// *0.4;

	float screenShotX = ofGetWidth() * screenshotXPrc;// -screenshotW - borderPaddingX;

	float textW = ofGetWidth() * textWPrc;// screenShotX - borderPaddingX * 1;

	//drawing the screenshot
	ofSetColor(255, alpha);
	screenshot.draw(screenShotX, startY, screenshotW, screenshotH);

	//outline
	ofColor outlineCol;
	outlineCol.setHex(outlineColHex);
	outlineCol.a = alpha;
	int outlineSize = 6;
	ofSetColor(outlineCol);
	//top
	ofRect(screenShotX - outlineSize, startY - outlineSize, screenshotW + outlineSize * 2, outlineSize);
	//bottom
	ofRect(screenShotX - outlineSize, startY + screenshotH, screenshotW + outlineSize * 2, outlineSize);
	//left
	ofRect(screenShotX - outlineSize, startY, outlineSize, screenshotH);
	//right
	ofRect(screenShotX + screenshotW, startY, outlineSize, screenshotH);

	
	float textX = ofGetWidth() * textXPrc;

	//title
	ofColor titleCol;
	titleCol.setHex(titleColHex);
	titleCol.a = alpha;
	ofSetColor(titleCol);
	float titleY = startY + titleFont->lineHeight;
	titleFont->draw(titleText, textX, titleY, textW);

	//by line
	float byY = titleY + titleFont->lineHeight + 60;
	byLineFont->draw(byLineText, textX, byY, textW);

	//by info
	ofColor infoCol;
	infoCol.setHex(textColHex);
	infoCol.a = alpha;
	ofSetColor(infoCol);
	float infoY = byY + byLineFont->lineHeight + 60;
	infoFont->draw(infoText, textX, infoY, textW);


}