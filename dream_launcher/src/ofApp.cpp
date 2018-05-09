#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	ofSetWindowTitle("dream_launcher");
	//FreeConsole();	//hides the console

	titleFont.setup("ChevyRay - Thicket Mono.ttf", 42);
	byLineFont.setup("ChevyRay - Thicket Mono.ttf", 34);
	infoFont.setup("ChevyRay - Thicket Mono.ttf", 28);
	infoFont.waveSize = 3;

	bottomInfoFont.load("ChevyRay - Thicket Mono.ttf", 13);

	selectionAnimationTime = 0.2f;
	selectionAnimationTimer = 0;

	topText.setup("Select Game");
	
	setScreenPoints();

	curSelection = 0;

	info.clear();
	icons.clear();
	loadXML();

	//icons
	/*
	icons.resize(6);
	icons[0].testCol = ofColor::red;
	icons[1].testCol = ofColor::royalBlue;
	icons[2].testCol = ofColor::purple;
	icons[3].testCol = ofColor::forestGreen;
	icons[4].testCol = ofColor::orange;
	icons[5].testCol = ofColor::paleTurquoise;
	*/
	
	for (int i = 0; i < icons.size(); i++) {
		icons[i].animCurve = 1;
		icons[i].idTestNum = i;
	}

	//game info
	
	//info.resize(icons.size());

	/*
	info[0].setup("BUNT", "By starbo", "thrilling thrilling thrilling. A thrilling time.", "none");
	info[1].setup("Flim Flam Quest", "By Jummie", "Is this quest for real... or it is a flim flam?.", "none");
	info[2].setup("Brine and Gore", "By Dang Sutinworry, Poundle Kram and Minchers", "Ride on a boat smacking aquatic life until it isn't there anymore.", "none");
	info[3].setup("Is this a nose?", "By Prinle & Chift", "Do you think you know the answer. If you can detect if it is a nose then you will get to wear the nose crown all day.", "none");
	info[4].setup("Copyright Smackdown", "By Mips Hallobew", "I found it on google! Is that ok for me to use?", "none");
	info[5].setup("The Tunnel That Wouldn't Stop", "By krim, kram and zootle", "Prepare to run infinitely, brother", "none");
	*/

	for (int i = 0; i < info.size(); i++) {
		info[i].titleFont = &titleFont;
		info[i].byLineFont = &byLineFont;
		info[i].infoFont = &infoFont;
		//info[i].testCol = icons[i].testCol;
	}

	dbaaLogo.load("dba_noText-01_small.png");

	cycleSelection(3, 4);
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
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//top text
	ofSetColor(0);
	topText.draw(ofGetWidth() / 2, ofGetHeight() * 0.04);

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
	ofTranslate(ofGetWidth()*0.05, ofGetHeight() * 0.94);
	ofSetColor(255);
	ofScale(logoScale, logoScale);
	ofRotate( ofMap( sin(ofGetElapsedTimef()), -1, 1, -10, -25) );
	dbaaLogo.draw(-dbaaLogo.getWidth() / 2, -dbaaLogo.getHeight() / 2);
	ofPopMatrix();

	//info
	string bottomInfoText = "Queer Matrixxx Arcade Machine brought to you by Death By Audio Arcade * DeathByAudioArcade.com * @DBAArcade * Give us some love";
	ofSetColor(0);
	bottomInfoFont.drawString(bottomInfoText, ofGetWidth() * 0.1, ofGetHeight() * 0.99);
}

//--------------------------------------------------------------
void ofApp::cycleSelection(int _oldSelection, int newSelection) {
	
	curSelection = newSelection;
	oldSelection = _oldSelection;

	selectionAnimationTimer = 0;

	//cout << "going from "<<oldSelection << " to " << curSelection << endl;

	bool goingUp = (oldSelection + 1) % icons.size() == curSelection;
	//cout << "go up " << goingUp << endl;

	float offScreenPadding = 400;

	//first push everything way off screen
	for (int i = 0; i < icons.size(); i++) {
		icons[i].animTimer = 9999;
		icons[i].startPos.x = 9999;
		icons[i].endPos.x = 9999;
		icons[i].startAnimation(selectionAnimationTime);
	}

	//then put the relevant ones in their starting positions
	for (int i = -2; i <= 2; i++) {	//this assumes 5 anchor points
		int thisID = (oldSelection + icons.size() + i) % icons.size();
		icons[thisID].startPos = iconAnchorPoints[i + 2];

		//assume the side ones will just go off screen
		if (i == -2 && goingUp) {
			icons[thisID].endPos.set(-offScreenPadding, iconAnchorPoints[0].y);
		}
		if (i == 2 && !goingUp) {
			icons[thisID].endPos.set(ofGetWidth() + offScreenPadding, iconAnchorPoints[4].y);
		}
	}

	//and the ending points
	for (int i = -2; i <= 2; i++) {	//this assumes 5 anchor points
		int thisID = (curSelection + icons.size() + i) % icons.size();
		icons[thisID].endPos = iconAnchorPoints[i + 2];
		//cout << i << " this icon " << thisID << endl;

		//assume the side ones will just come from off screen
		if (i == -2 && !goingUp) {
			icons[thisID].startPos.set(-offScreenPadding, iconAnchorPoints[0].y);
		}
		if (i == 2 && goingUp) {
			icons[thisID].startPos.set(ofGetWidth() + offScreenPadding, iconAnchorPoints[4].y);
		}
	}

	//testing
	/*
	for (int i = 0; i < icons.size(); i++) {
		cout << i << " start " << icons[i].startPos.x << "  end " << icons[i].endPos.x << endl;
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//left and right
	if (key == 'a' || key == 'A' || key == OF_KEY_LEFT) {
		cycleSelection(curSelection, (curSelection + icons.size() - 1) % icons.size());
	}
	if (key == 'd' || key == 'D' || key == OF_KEY_RIGHT) {
		cycleSelection(curSelection, (curSelection + 1) % icons.size());
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
