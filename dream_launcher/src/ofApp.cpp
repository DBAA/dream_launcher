#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 180, 180);
	ofEnableAlphaBlending();

	cout << "LEVER UP!" << endl;

	ofDirectory games_dir = ofDirectory("games");
	games_folder_path = games_dir.getAbsolutePath();
	//cout << games_folder_path << endl;


	ofSetWindowTitle("dream_launcher_app");

	background.setup();

	info.clear();
	icons.clear();
	loadXML();

	returnSound.play();

	selectionAnimationTime = 0.2f;
	selectionAnimationTimer = 0;

	curSelection = (int)ofRandom(icons.size());

	canSelectGame = true;

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
	}

	//logo.load("dba_noText-01_small_white.png");



	cycleSelection(curSelection, curSelection);

}
//--------------------------------------------------------------
void ofApp::loadXML() {
	ofXml xml;
	if (xml.load("games.xml") == false) {
		cout << "bad games xml file" << endl;
		return;
	}

	confirm_keys.clear();
	left_keys.clear();
	right_keys.clear();

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
				thisGameInfo.isWeb = true;
			}
		}

		icons.push_back(thisIcon);
		info.push_back(thisGameInfo);
	} while (xml.setToSibling());

	xml.setToParent();
	

	//other settings
	if (xml.load("settings.xml") == false) {
		cout << "bad settings file" << endl;
		return;
	}
	xml.setTo("SETTINGS");
	background.bgGray = xml.getValue<int>("BG_GRAY");
	background.bgAlpha = xml.getValue<int>("BG_ALPHA");

	xml.setTo("BG_COLORS");
	xml.setTo("BG_COLOR[0]");
	do {
		string hex = xml.getValue<string>("VAL");
		//cout << " bg color: " << hex << endl;

		unsigned int r, g, b, a = 255; // Default alpha to 255
		std::stringstream ss;
		ss << std::hex;

		// Parse red, green, blue
		ss << hex.substr(1, 2); ss >> r; ss.clear();
		ss << hex.substr(3, 2); ss >> g; ss.clear();
		ss << hex.substr(5, 2); ss >> b;

		// If alpha channel exists, parse it
		if (hex.length() == 9) {
			ss.clear();
			ss << hex.substr(7, 2); ss >> a;
		}

		//cout << "  " << r << " , " << g << " , " << b << " , " << a << endl;

		background.colors.push_back( ofColor(r, g, b, a) );

		
	} while (xml.setToSibling());
	xml.setToParent();
	xml.setToParent();

	bottomMessageText = xml.getValue<string>("BOTTOM_MESSAGE");

	string logo_path = "images/" + xml.getValue<string>("LOGO_IMG");
	logo.load(logo_path);

	//keys
	xml.setTo("KEY_LEFT");
	xml.setTo("KEY[0]");
	do {
		int key_val = xml.getValue<int>("VAL");
		if (key_val == 0) {
			string val_s = xml.getValue<string>("VAL");
			if (val_s.length() > 0) {
				key_val = (int)val_s[0];
			}
		}
		left_keys.push_back(key_val);

	} while (xml.setToSibling());
	xml.setToParent();
	xml.setToParent();

	xml.setTo("KEY_RIGHT");
	xml.setTo("KEY[0]");
	do {
		int key_val = xml.getValue<int>("VAL");
		if (key_val == 0) {
			string val_s = xml.getValue<string>("VAL");
			if (val_s.length() > 0) {
				key_val = (int)val_s[0];
			}
		}
		right_keys.push_back(key_val);
		cout << "right push: " << key_val << endl;

	} while (xml.setToSibling());
	xml.setToParent();
	xml.setToParent();

	xml.setTo("KEY_CONFIRM");
	xml.setTo("KEY[0]");
	do {
		int key_val = xml.getValue<int>("VAL");
		if (key_val == 0) {
			string val_s = xml.getValue<string>("VAL");
			if (val_s.length() > 0) {
				key_val = (int)val_s[0];
			}
		}
		confirm_keys.push_back(key_val);
		cout << "confirm push: " << key_val << endl;

	} while (xml.setToSibling());
	xml.setToParent();
	xml.setToParent();

	/*cout << "OF_KEY_UP :" << OF_KEY_UP << endl;
	cout << "OF_KEY_DOWN :" << OF_KEY_DOWN << endl;
	cout << "OF_KEY_LEFT :" << OF_KEY_LEFT << endl;
	cout << "OF_KEY_RIGHT :" << OF_KEY_RIGHT << endl;
	cout << "OF_KEY_BACKSPACE :" << OF_KEY_BACKSPACE << endl;
	cout << "OF_KEY_RETURN :" << OF_KEY_RETURN << endl;*/


	//colors
	selectTextColHex = ofHexToInt(xml.getValue<string>("SELECT_HEX_COL"));
	gameTitleColHex = ofHexToInt(xml.getValue<string>("TITLE_HEX_COL"));
	gameInfoColHex = ofHexToInt(xml.getValue<string>("INFO_HEX_COL"));
	bottomTextColHex = ofHexToInt(xml.getValue<string>("BOTTOM_MESSAGE_HEX_COL"));
	outlineColHex = ofHexToInt(xml.getValue<string>("OUTLINE_HEX_COL"));

	//fonts
	titleFont.setup("fonts/"+xml.getValue<string>("TITLE_FONT"), xml.getValue<int>("TITLE_FONT_SIZE"));
	byLineFont.setup("fonts/" + xml.getValue<string>("BY_LINE_FONT"), xml.getValue<int>("BY_LINE_FONT_SIZE"));
	infoFont.setup("fonts/" + xml.getValue<string>("INFO_FONT"), xml.getValue<int>("INFO_FONT_SIZE"));
	infoFont.waveSize = 3;

	bottomInfoFont.load("fonts/" + xml.getValue<string>("BOTTOM_FONT"), xml.getValue<int>("BOTTOM_FONT_SIZE"));

	topText.setup(xml.getValue<string>("TOP_TEXT_MESSAGE"), "fonts/"+xml.getValue<string>("TOP_TEXT_FONT"), xml.getValue<int>("TOP_TEXT_FONT_SIZE") );

	//audio
	moveSound.load("sounds/" + xml.getValue<string>("MOVE_SOUND"));
	selectSound.load("sounds/" + xml.getValue<string>("SELECT_SOUND"));
	returnSound.load("sounds/" + xml.getValue<string>("RETURN_SOUND"));

	//placement
	selectGameY = xml.getValue<float>("SELECT_GAME_Y");

	iconY = xml.getValue<float>("ICON_Y");
	iconYSpacing = xml.getValue<float>("ICON_Y_SPACING");
	iconXSpacing = xml.getValue<float>("ICON_X_SPACING");
	iconSpacingCurve = xml.getValue<float>("ICON_SPACING_CURVE");

	float gameInfoTextY = xml.getValue<float>("GAME_INFO_TEXT_Y_START");
	float gameTextX = xml.getValue<float>("GAME_TEXT_X");
	float gameTextW = xml.getValue<float>("GAME_TEXT_W");
	float gameTextByLineSpacing = xml.getValue<float>("GAME_TEXT_BY_LINE_SPACING");
	float gameTextInfoSpacing = xml.getValue<float>("GAME_TEXT_INFO_SPACING");
	float screenshotW = xml.getValue<float>("SCREEN_SHOT_WIDTH");
	float screenshotX = xml.getValue<float>("SCREEN_SHOT_X");
	float screenshotY = xml.getValue<float>("SCREEN_SHOT_Y");
	bool use_text_for_general_info = xml.getValue<string>("USE_IMAGE_FOR_DREAMHOUSE_INFO") == "TRUE";
	cout << "ima do " << use_text_for_general_info << endl;
	for (int i = 0; i < info.size(); i++) {
		info[i].textStartYPrc = gameInfoTextY;
		info[i].textXPrc = gameTextX;
		info[i].textWPrc = gameTextW;
		info[i].textByLineYSpacingPrc = gameTextByLineSpacing;
		info[i].textInfoYSpacingPrc = gameTextInfoSpacing;
		info[i].screenshotW = screenshotW;
		info[i].screenshotXPrc = screenshotX;
		info[i].screenshotYPrc = screenshotY;
		info[i].show_image_for_general_info = use_text_for_general_info;
	}

	float icon_w = xml.getValue<float>("ICON_WIDTH");
	float icon_h = xml.getValue<float>("ICON_HEIGHT");
	for (int i = 0; i < icons.size(); i++) {
		icons[i].icon_w = icon_w;
		icons[i].icon_h = icon_h;
	}

	logoPos.x = xml.getValue<float>("LOGO_X");
	logoPos.y = xml.getValue<float>("LOGO_Y");
	bottomTextPos.x = xml.getValue<float>("BOTTOM_TEXT_X");
	bottomTextPos.y = xml.getValue<float>("BOTTOM_TEXT_Y");

	if (xml.getValue<string>("HIDE_CONSOLE") == "TRUE") {
		FreeConsole();	//hides the console
	}

	use_relative_path = xml.getValue("USE_RELATIVE_PATH") == "TRUE";

	closeAfterLaunchingGame = xml.getValue<string>("CLOSE_AFTER_GAME_LAUNCH") == "TRUE";
	cout << "close after launch " << closeAfterLaunchingGame << endl;

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
	
	

	float selectionAnimPrc = selectionAnimationTimer / selectionAnimationTime;
	selectionAnimPrc = MIN(selectionAnimPrc, 1);
	//draw the info for this game, crossfading when the seleciton changes
	info[curSelection].draw(255 * selectionAnimPrc, gameTitleColHex, gameInfoColHex, outlineColHex);
	
	if (selectionAnimPrc < 1.0) {
		info[oldSelection].draw(255 * (1.0 - selectionAnimPrc), gameTitleColHex, gameInfoColHex, outlineColHex);
	}


	//top text
	ofSetHexColor(selectTextColHex);
	topText.draw(ofGetWidth() / 2, ofGetHeight() * selectGameY);

	//icons
	for (int i = 0; i < icons.size(); i++) {
		icons[i].draw(outlineColHex);
	}

	//bottom stuff
	ofColor bottomTextCol;
	bottomTextCol.setHex(bottomTextColHex);
	float zeno = 0.1;
	if (info[curSelection].is_general_info) {
		bottomTextAlpha *= (1.0-zeno);
	}
	else {
		bottomTextAlpha = (1.0-zeno) * bottomTextAlpha +  (zeno)*255.0;
	}
	if (info[curSelection].show_image_for_general_info == false) {
		bottomTextAlpha = 255;
	}
	bottomTextCol.a = bottomTextAlpha;

	//logo
	ofSetColor(bottomTextCol);
	float logoScale = 0.35;
	ofPushMatrix();
	ofTranslate(ofGetWidth() * logoPos.x, ofGetHeight() * logoPos.y);
	ofScale(logoScale, logoScale);
	ofRotate( ofMap( sin(ofGetElapsedTimef()), -1, 1, -10, -25) );
	logo.draw(-logo.getWidth() / 2, -logo.getHeight() / 2);
	ofPopMatrix();

	//info
	//ofSetHexColor(bottomTextColHex);
	float bottom_text_w = bottomInfoFont.stringWidth(bottomMessageText);
	bottomInfoFont.drawString(bottomMessageText, ofGetWidth() * bottomTextPos.x - bottom_text_w/2, ofGetHeight() * bottomTextPos.y);
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
	pos.y = ofGetHeight() * iconY - abs(slotNum) * ofGetHeight() * iconYSpacing;
	
	float distPrc = (float)slotNum / 3.0;
	float curvePrc = powf(abs(distPrc), iconSpacingCurve);
	float spacing = ofGetWidth() * iconXSpacing;
	if (slotNum < 0)	spacing *= -1;
	pos.x = ofGetWidth() / 2 + curvePrc * spacing;

	return pos;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//cout << "ya pressed " << key << endl;
	//this command is used by the autohotkey script and is called whenever the app is given focus
	if (key == 'R') {
		cout << "better resize" << endl;
		returnSound.play();
		if (isFullScreened() == false) {
			ofToggleFullscreen();
		}
		canSelectGame = true;
	}

	//trying out just killing all input if the autohotkey script hasn't told us it's OK
	if (!canSelectGame) {
		return;
	}

	bool left_pressed = false;
	for (int i = 0; i < left_keys.size(); i++)	if (key == left_keys[i]) left_pressed = true;
	if (left_pressed) {
		cycleSelection(curSelection, (curSelection + icons.size() - 1) % icons.size());
		background.offsetInt--;
		moveSound.play();
	}
	bool right_pressed = false;
	for (int i = 0; i < right_keys.size(); i++)	if (key == right_keys[i]) right_pressed = true;
	if (right_pressed) {
		cycleSelection(curSelection, (curSelection + 1) % icons.size());
		background.offsetInt++;
		moveSound.play();
	}


	bool confirm_pressed = false;
	for (int i = 0; i < confirm_keys.size(); i++)	if (key == confirm_keys[i]) confirm_pressed = true;

	//all player buttons act as selecitons
	if(confirm_pressed & canSelectGame){
		if (info[curSelection].is_general_info == false) {
			cout << "launch " << info[curSelection].titleText << endl;
			selectSound.play();
			if (info[curSelection].isWeb) {
				//ofToggleFullscreen();
				launchWeb(info[curSelection].executablePath);
			}
			else {
				launchExe(info[curSelection].executablePath);
			}
		}
	}

	//testing. should this be removed?
	if (key == 'f') {
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
void ofApp::launchExe(string _path) {
	if (isFullScreened()) {
		ofToggleFullscreen();
	}

	string path = _path;
	if (use_relative_path) {
		path = games_folder_path + _path;
	}
	//cout << "launch:" << path << endl;

	std::wstring pathTemp = std::wstring(path.begin(), path.end());
	LPCWSTR pathLPC = pathTemp.c_str();

	string command = "open";
	std::wstring commandTemp = std::wstring(command.begin(), command.end());
	LPCWSTR commandLPC = commandTemp.c_str();
	 
	ShellExecute(NULL, commandLPC, pathLPC, NULL, NULL, SW_SHOWDEFAULT);
	
	canSelectGame = false;

	if (closeAfterLaunchingGame) {
		ofExit();
	}
}


//--------------------------------------------------------------
void ofApp::launchWeb(string url) {
	if (isFullScreened()) {
		ofToggleFullscreen();
	}

	std::wstring pathTemp = std::wstring(url.begin(), url.end());
	LPCWSTR pathLPC = pathTemp.c_str();

	ShellExecute(0, 0, pathLPC, 0, 0, SW_MAXIMIZE);

	canSelectGame = false;
	if (closeAfterLaunchingGame) {
		ofExit();
	}
}

//--------------------------------------------------------------
bool ofApp::isFullScreened() {
	return ofGetHeight() == ofGetScreenHeight();
}
