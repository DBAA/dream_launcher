#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 180, 180);
	ofEnableAlphaBlending();

	ofSetWindowTitle("dream_launcher");
	//FreeConsole();	//hides the console

	titleFont.setup("ChevyRay - Thicket Mono.ttf", 42);
	byLineFont.setup("ChevyRay - Thicket Mono.ttf", 34);
	infoFont.setup("ChevyRay - Thicket Mono.ttf", 28);
	infoFont.waveSize = 3;

	bottomInfoFont.load("ChevyRay - Thicket Mono.ttf", 15);

	selectionAnimationTime = 0.2f;
	selectionAnimationTimer = 0;

	topText.setup("Select Game");
	
	setScreenPoints();

	curSelection = 0;

	info.clear();
	icons.clear();
	loadXML();

	//icon basic settings
	for (int i = 0; i < icons.size(); i++) {
		icons[i].animCurve = 1;
		icons[i].idTestNum = i;
	}

	//info basic settings
	for (int i = 0; i < info.size(); i++) {
		info[i].titleFont = &titleFont;
		info[i].byLineFont = &byLineFont;
		info[i].infoFont = &infoFont;
		//info[i].testCol = icons[i].testCol;
	}

	dbaaLogo.load("dba_noText-01_small.png");


	background.setup();

	cycleSelection(1, 1);

}
//--------------------------------------------------------------
void ofApp::loadXML() {
	ofXml xml;
	if (xml.load("games.xml") == false) {
		cout << "bad xml file" << endl;
		return;
	}

	//go through the games
	xml.setTo("GAME[0]");
	do {
		GameIcon thisIcon;
		thisIcon.iconPic.load("images/"+xml.getValue<string>("ICON"));

		GameInfo thisGameInfo;
		string gameTitle = xml.getValue<string>("TITLE");
		string byLine = xml.getValue<string>("CREDITS");
		string infoText = xml.getValue<string>("INFO");
		string path = xml.getValue<string>("EXE_PATH");
		thisGameInfo.setup(gameTitle, byLine, infoText, path);
		thisGameInfo.screenshot.load("images/" + xml.getValue<string>("SCREENSHOT"));
		if (xml.exists("IS_WEB")) {
			if (xml.getValue<bool>("IS_WEB")) {
				cout << "web is real" << endl;
				thisGameInfo.isWeb = true;
			}
		}

		icons.push_back(thisIcon);
		info.push_back(thisGameInfo);
	} while (xml.setToSibling());
	/*
	if (xml.exists("GAME")) {
		cout << "it there" << endl;
		xml.setTo("GAME[0]");
		
	}
	*/


}

//--------------------------------------------------------------
void ofApp::setScreenPoints() {
	for (int i = 0; i < NUM_ICON_ANCHORS; i++) {
		iconAnchorPoints[i].y = ofGetHeight() * 0.23f;
	}

	iconAnchorPoints[2].x = ofGetWidth() * 0.5;
	float dist1 = ofGetWidth() * 0.27;
	float dist2 = ofGetWidth() * 0.48;
	iconAnchorPoints[3].x = ofGetWidth() / 2 + dist1;
	iconAnchorPoints[4].x = ofGetWidth() / 2 + dist2;

	iconAnchorPoints[1].x = ofGetWidth() / 2 - dist1;
	iconAnchorPoints[0].x = ofGetWidth() / 2 - dist2;

}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < icons.size(); i++) {
		icons[i].update();
	}

	selectionAnimationTimer += ofGetLastFrameTime();

	background.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//background
	background.draw();
	
	//top text
	ofSetColor(0);
	topText.draw(ofGetWidth() / 2, ofGetHeight() * 0.05);

	//icons
	for (int i = 0; i < icons.size(); i++) {
		icons[i].draw();
	}

	float selectionAnimPrc = selectionAnimationTimer / selectionAnimationTime;
	selectionAnimPrc = MIN(selectionAnimPrc, 1);
	//draw the info for this game, crossfading when the seleciton changes
	info[curSelection].draw(255 * selectionAnimPrc);
	
	if (selectionAnimPrc < 1.0) {
		info[oldSelection].draw(255 * (1.0 - selectionAnimPrc));
	}


	//logo
	float logoScale = 0.35;
	ofPushMatrix();
	ofTranslate(ofGetWidth()*0.06, ofGetHeight() * 0.94);
	ofSetColor(255);
	ofScale(logoScale, logoScale);
	ofRotate( ofMap( sin(ofGetElapsedTimef()), -1, 1, -10, -25) );
	dbaaLogo.draw(-dbaaLogo.getWidth() / 2, -dbaaLogo.getHeight() / 2);
	ofPopMatrix();

	//info
	string bottomInfoText = "DreamboxXx Arcade Machine brought to you by Death By Audio Arcade * DeathByAudioArcade.com * @DBAArcade";
	ofSetColor(0);
	bottomInfoFont.drawString(bottomInfoText, ofGetWidth() * 0.12, ofGetHeight() * 0.97);
}

//--------------------------------------------------------------
void ofApp::cycleSelection(int _oldSelection, int newSelection) {
	
	curSelection = newSelection;
	oldSelection = _oldSelection;

	selectionAnimationTimer = 0;

	//cout << "going from "<<oldSelection << " to " << curSelection << endl;

	bool goingUp = (oldSelection + 1) % icons.size() == curSelection;
	
	//set the positions
	for (int i = 0; i < icons.size(); i++) {
		int endOrder = getRelativeIconOrder(i);
		int startOrder = getRelativeIconOrder(i - 1);
		if (goingUp) {
			startOrder = getRelativeIconOrder(i + 1);
		}
		icons[i].startPos = getIconPos( startOrder );
		icons[i].endPos = getIconPos(endOrder);

		//dumb error checking
		if ((icons[i].startPos.x < 0 && icons[i].endPos.x > ofGetWidth()) || (icons[i].startPos.x > ofGetWidth() && icons[i].endPos.x < 0)) {
			icons[i].startPos = icons[i].endPos;
		}

		//kick it off
		icons[i].startAnimation(selectionAnimationTime);
	}


}

//--------------------------------------------------------------
int ofApp::getRelativeIconOrder(int iconID) {
	int relativePos = iconID - curSelection;
	if (relativePos < -4) {
		relativePos += icons.size();
	}
	if (relativePos > 4) {
		relativePos -= icons.size();
	}
	return relativePos;
}

//--------------------------------------------------------------
//0 is center
ofVec2f ofApp::getIconPos(int slotNum) {
	ofVec2f pos;
	pos.y = ofGetHeight() * 0.23 - abs(slotNum) * ofGetHeight() * 0.01;
	
	float distPrc = (float)slotNum / 3.0;
	float curvePrc = powf(abs(distPrc), 0.85);
	float spacing = ofGetWidth() * 0.55;
	if (slotNum < 0)	spacing *= -1;
	pos.x = ofGetWidth() / 2 + curvePrc * spacing;

	return pos;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//left and right
	if (key == 'a' || key == 'A' || key == OF_KEY_LEFT) {
		cycleSelection(curSelection, (curSelection + icons.size() - 1) % icons.size());
		background.offsetInt--;
	}
	if (key == 'd' || key == 'D' || key == OF_KEY_RIGHT) {
		cycleSelection(curSelection, (curSelection + 1) % icons.size());
		background.offsetInt++;
	}

	//all player buttons act as selecitons
	if (key == 'C' || key == 'c' || key == 'V' || key == 'v' || key == 'N' || key == 'n' || key == 'M' || key == 'm') {
		cout << "launch " << info[curSelection].titleText << endl;
		if (info[curSelection].isWeb) {
			ofToggleFullscreen();
			launchWeb(info[curSelection].executablePath);
		}
		else {
			launchExe(info[curSelection].executablePath);
		}
	}

	//cout << "ya pressed " << key << endl;
	if (key == '1') {
		launchExe("C:/Users/andy_/Documents/dbaa_launcher/bleep_space_win_1.55/BleepSpace.exe");
	}
	if (key == '2') {
		ofToggleFullscreen();
		launchWeb("C:/Users/andy_/Documents/dbaa_launcher/textagon/textagon.html");
	}

	//testing. this should be RREgone
	if (key == 'f') {
		ofToggleFullscreen();
	}

	if (key == 'R') {
		cout << "better resize" << endl;
		if (isFullScreened() == false) {
			ofToggleFullscreen();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	setScreenPoints();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::launchExe(string path) {
	if (isFullScreened()) {
		ofToggleFullscreen();
	}

	std::wstring pathTemp = std::wstring(path.begin(), path.end());
	LPCWSTR pathLPC = pathTemp.c_str();

	string command = "open";
	std::wstring commandTemp = std::wstring(command.begin(), command.end());
	LPCWSTR commandLPC = commandTemp.c_str();
	 
	ShellExecute(NULL, commandLPC, pathLPC, NULL, NULL, SW_SHOWDEFAULT);
	
}


//--------------------------------------------------------------
void ofApp::launchWeb(string url) {
	if (isFullScreened()) {
		ofToggleFullscreen();
	}

	std::wstring pathTemp = std::wstring(url.begin(), url.end());
	LPCWSTR pathLPC = pathTemp.c_str();

	ShellExecute(0, 0, pathLPC, 0, 0, SW_MAXIMIZE);

}

//--------------------------------------------------------------
bool ofApp::isFullScreened() {
	return ofGetHeight() == ofGetScreenHeight();
}
