#include "BounceText.h"

void BounceText::setup(string fontPath, int _fontSize) {
	font.loadFont(fontPath, _fontSize);
	fontSize = _fontSize;

	waveSpeed = 2;
	waveStep = 0.4f;
	waveSize = fontSize * 0.2;

	charSpacing = 1 + fontSize * 0.1;
	spaceWidth = font.stringWidth("o");
	lineHeight = font.getLineHeight() * 1.25;

	line_break_marker = "#";
}

//returns height of the text
float BounceText::draw(string textToDraw, int _x, int _y, int textWidth) {
	
	//cout << "space " << spaceWidth << endl;

	//break it up into words
	vector<string> words;
	string thisWord = "";
	for (int i = 0; i < textToDraw.length(); i++) {
		if (textToDraw[i] == ' ' || textToDraw[i] == '\n') {
			words.push_back(thisWord);
			thisWord = "";

			if (textToDraw[i] == '\n') {
				words.push_back(line_break_marker);
			}
		}
		else {
			thisWord += textToDraw[i];
		}
	}
	words.push_back(thisWord);

	//break that up into lines
	string thisLine = "";
	float curWidth = 0;
	int lineNum = 0;
	//int charNum = 0;
	for (int i = 0; i < words.size(); i++) {
		//cout << "word: " << words[i] << endl;
		//if the next word would push us off the line, end it
		if (curWidth + font.stringWidth(words[i]) + charSpacing*words[i].length() > textWidth || words[i] == line_break_marker) {
			drawLine(thisLine, _x, _y + lineNum * lineHeight, 0);
			lineNum++;
			curWidth = 0;
			thisLine = "";
		}
		if (words[i] != line_break_marker) {
			//add the next word
			thisLine += words[i];
			thisLine += " ";
			curWidth += font.stringWidth(words[i]) + charSpacing * words[i].length();
			curWidth += spaceWidth;
		}

	}

	//draw the last line
	if (thisLine.length() > 0) {
		drawLine(thisLine, _x, _y + lineNum * lineHeight, 0);
	}

	//the text goes up form the given Y, so if it is only 1 line, it will extend 0 below that line
	return (lineNum ) * lineHeight;

}

void BounceText::drawLine(string lineText, int _x, int _y, int charStartNum) {
	float curX = _x;
	for (int i = 0; i < lineText.length(); i++) {
		if (lineText[i] != ' ') {
			string thisChar = "";
			thisChar += lineText[i];
			float thisX = curX;
			float thisY = _y + sin(ofGetElapsedTimef() * waveSpeed + waveStep*(charStartNum+i)) * waveSize;
			font.drawString(thisChar, thisX, thisY);
			curX += font.stringWidth(thisChar) + charSpacing;
		}
		else {
			curX += spaceWidth;
		}
	}
}