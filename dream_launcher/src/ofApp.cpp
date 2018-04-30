#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	ofSetWindowTitle("dream_launcher");
	//FreeConsole();	//hides the console

	testFont.setup("ChevyRay - Thicket Mono.ttf", 20);

	selectionAnimationTime = 0.2f;
	
	setScreenPoints();

	curSelection = 0;

	icons.resize(7);
	icons[0].testCol = ofColor::red;
	icons[1].testCol = ofColor::royalBlue;
	icons[2].testCol = ofColor::purple;
	icons[3].testCol = ofColor::forestGreen;
	icons[4].testCol = ofColor::orange;
	icons[5].testCol = ofColor::paleTurquoise;
	icons[6].testCol = ofColor::goldenRod;

	for (int i = 0; i < icons.size(); i++) {
		icons[i].animCurve = 1;
		icons[i].idTestNum = i;
	}

	cycleSelection(3, 4);
}

//--------------------------------------------------------------
void ofApp::setScreenPoints() {
	for (int i = 0; i < NUM_ICON_ANCHORS; i++) {
		iconAnchorPoints[i].y = ofGetHeight() * 0.15f;
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
}

//--------------------------------------------------------------
void ofApp::draw(){
	

	//icons
	for (int i = 0; i < icons.size(); i++) {
		icons[i].draw();
	}

	//test text

	ofSetColor(0);
	testFont.draw("Hello my sweet baby. How are you on this Hello fine day?", 40, ofGetHeight() - 100, 800);

	ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
	ofDrawBitmapString(ofToString(ofGetWidth()) + "  " + ofToString(ofGetHeight()), 100, 600);


	//testing
	//cout << "icon x " << icons[3].pos.x << endl;

}

//--------------------------------------------------------------
void ofApp::cycleSelection(int _oldSelection, int newSelection) {
	
	curSelection = newSelection;
	oldSelection = _oldSelection;

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
void ofApp::keyPressed(int key){
	if (key == 'a') {
		cycleSelection(curSelection, (curSelection+icons.size()-1)%icons.size());
	}
	if (key == 'd') {
		cycleSelection(curSelection, (curSelection + 1) % icons.size());
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
