#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("dream_launcher");
	FreeConsole();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
	ofDrawBitmapString("DREAM", ofGetWidth()/2, ofGetHeight() / 2);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1') {
		launchExe("C:/Users/andy_/Documents/dbaa_launcher/bleep_space_win_1.55/BleepSpace.exe");
	}

	if (key == 't') {
		ofToggleFullscreen();
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::launchExe(string path) {
	std::wstring pathTemp = std::wstring(path.begin(), path.end());
	LPCWSTR pathLPC = pathTemp.c_str();

	string command = "open";
	std::wstring commandTemp = std::wstring(command.begin(), command.end());
	LPCWSTR commandLPC = commandTemp.c_str();
	 
	ShellExecute(NULL, commandLPC, pathLPC, NULL, NULL, SW_SHOWDEFAULT);
}