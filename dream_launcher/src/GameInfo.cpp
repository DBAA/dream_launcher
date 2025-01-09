#include "GameInfo.h"

void GameInfo::setup(string title, string byLine, string info, string path) {
	titleText = title;
	byLineText = byLine;
	infoText = info;

	//this does not work
	/*for (int i = 0; i < infoText.size(); i++) {
		if (infoText[i] == '#')	infoText[i] = '\n';
	}*/

	executablePath = path;
	isWeb = false;

	is_general_info = title == "general_info";
	show_image_for_general_info = true;
}

void GameInfo::draw(float alpha, int titleColHex, int textColHex, int outlineColHex) {
	//float screenshotW = 720;
	//float screenshotH = 540;

	//float borderPaddingX = 100;
	float textStartY = ofGetHeight() * textStartYPrc;

	

	float textW = ofGetWidth() * textWPrc;
	float textX = ofGetWidth() * textXPrc;

	//games
	if (!is_general_info) {
		float ratio = (float)screenshot.getHeight() / (float)screenshot.getWidth();
		float screenshotH = screenshotW * ratio;

		float screenShotX = ofGetWidth() * screenshotXPrc - screenshotW/2 ;
		float screenShotY = ofGetHeight() * screenshotYPrc - screenshotH/2;


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

		//image only
		if (show_image_for_general_info) {
			ofSetColor(255, alpha);
			float screenshotH = ofGetHeight();
			float screenShotY = 0;
			//screenshotH = screenshot.getHeight();
			float screenshotW = screenshotH * ((float)screenshot.getWidth() / (float)screenshot.getHeight());
			float screenShotX = ofGetWidth() / 2 - screenshotW / 2;
			//screenshotW = ofGetWidth() - screenShotX * 2;
			screenshot.draw(screenShotX, screenShotY, screenshotW, screenshotH);
		}
		//text only
		/*else {
			ofColor infoCol;
			infoCol.setHex(textColHex);
			infoCol.a = alpha;
			ofSetColor(infoCol);
			float infoY = textStartY + titleFont->lineHeight;
			infoFont->draw(infoText, screenShotX, infoY, ofGetWidth() - screenShotX * 2);
		}*/
	}
	

	
	

	


}