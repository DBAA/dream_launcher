//
//  Background.hpp
//  dream_jam_tetsing
//
//  Created by Andrew Wallace on 5/16/18.
//

#ifndef Background_hpp
#define Background_hpp

#include "ofMain.h"

class Background{
public:
    
    void setup();
    void update();
    void draw();
    
    vector<ofColor> colors;
    ofImage barPic;
    
    int offsetInt;
    float offsetY;

	int bgGray, bgAlpha;
    
    
};

#endif /* Background_hpp */
