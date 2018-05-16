#pragma once

#include "ofMain.h"
#include "BounceText.h"
#include "GameIcon.h"
#include "GameInfo.h"
#include "TopText.h"
#include "Background.hpp"
#include <windows.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void loadXML();
		void setScreenPoints();
		void update();
		void draw();

		void cycleSelection(int _oldSelection, int newSelection);


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void launchExe(string path);
		void launchWeb(string url);

		bool isFullScreened();


		BounceText titleFont, byLineFont, infoFont;

		vector<GameIcon> icons;
		vector<GameInfo> info;
		int curSelection, oldSelection;

		float selectionAnimationTime;
		float selectionAnimationTimer;

#define NUM_ICON_ANCHORS 5
		ofVec2f iconAnchorPoints[NUM_ICON_ANCHORS];

		TopText topText;

		ofImage dbaaLogo;
		ofTrueTypeFont bottomInfoFont;

		Background background;
		
};
