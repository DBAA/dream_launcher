//
//  Background.cpp
//  dream_jam_tetsing
//
//  Created by Andrew Wallace on 5/16/18.
//

#include "Background.hpp"


void Background::setup(){
    
    barPic.load("bg_bar.png");
    
    //http://www.colourlovers.com/palette/1250813/Pastel_Rainbow
   /* colors.push_back( ofColor(255,171,171));
    colors.push_back( ofColor(255,218,171));
    colors.push_back( ofColor(221,255,171));
    colors.push_back( ofColor(171,228,255));
    colors.push_back( ofColor(217,171,255));*/
    
    offsetInt = 0;
    offsetY = 0;
}

void Background::update(){
    
    float xeno = 0.95;
    float yStep = 200;
    
    float targetY = offsetInt * yStep;
    offsetY = xeno * offsetY + (1.0f-xeno) * targetY;
    
    
}

void Background::draw(){
    float paddingY = barPic.getHeight();
    float barH = 200;
    
    float curY = offsetY;
    int curCol = 0;
    
    int testo = 0;
    while(curY > -paddingY){
        testo++;
        curY -= barH;
        curCol --;
        if (curCol < 0){
            curCol = colors.size()-1;
        }
    }
    //cout<<"move it back "<<testo<<" times"<<endl;
    
    testo = 0;
    while (curY < -paddingY){
        testo++;
        curY += barH;
        curCol++;
        if (curCol >= colors.size()){
            curCol = 0;
        }
    }
    //cout<<"move it forward "<<testo<<" times"<<endl;
    
    //actually draw them
    
    int totalDrawn = 0;
    while (curY < ofGetHeight() + barH){
        
        float distPrc = curY/ofGetHeight();
        float extraSpacing = powf( distPrc, 2) * 1000 ;//(curY - ofGetHeight()/2) * 0.9;
		//extraSpacing = MAX(extraSpacing, -barH);
        
		float thisY = curY + extraSpacing -70;
        
        //cout<<"y "<<curY<<"  extra "<<extraSpacing<<"  final "<<thisY<<endl;
        
        ofSetColor(colors[curCol]);
        barPic.draw(0, thisY);
        
        curCol ++;
        if (curCol >= colors.size()){
            curCol = 0;
        }
        curY += barH;
        
        totalDrawn++;
    }
    
    //cout<<"I drew "<<totalDrawn<<endl;
    
    
    //fade the whole thing out
	ofSetColor(bgGray, bgAlpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    
    
}
