#include "GameInfo.h"

void GameInfo::setup(string title, string byLine, string info, string path) {
	titleText = title;
	byLineText = byLine;
	infoText = info;
	executablePath = path;
	isWeb = false;

	is_general_info = title == "general_info";
}

void GameInfo::draw(float alpha, int titleColHex, int textColHex, int outlineColHex) {
	float screenshotW = 720;
	float screenshotH = 540;

	//float borderPaddingX = 100;
	float textStartY = ofGetHeight() * textStartYPrc;

	float screenShotX = ofGetWidth() * screenshotXPrc;
	float screenShotY = ofGetHeight() * screenshotYPrc;

	float textW = ofGetWidth() * textWPrc;
	float textX = ofGetWidth() * textXPrc;

	
	if (!is_general_info) {
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

		//title
		ofColor titleCol;
		titleCol.setHex(titleColHex);
		titleCol.a = alpha;
		ofSetColor(titleCol);
		float titleY = textStartY + titleFont->lineHeight;
		float titleHeight = titleFont->draw(titleText, textX, titleY, textW);

		//by line
		float byY = titleY + titleHeight + ofGetHeight() * textByLineYSpacingPrc;
		float byLineHeight = byLineFont->draw(byLineText, textX, byY, textW);

		//info
		ofColor infoCol;
		infoCol.setHex(textColHex);
		infoCol.a = alpha;
		ofSetColor(infoCol);
		float infoY = byY + byLineHeight + ofGetHeight() * textInfoYSpacingPrc;
		infoFont->draw(infoText, textX, infoY, textW);
	}
	//the special generla info page is just text
	else {
		ofColor infoCol;
		infoCol.setHex(textColHex);
		infoCol.a = alpha;
		ofSetColor(infoCol);
		float infoY = textStartY + titleFont->lineHeight;
		infoFont->draw(infoText, screenShotX, infoY, ofGetWidth()-screenShotX*2);
	}
	

	
	

	


}