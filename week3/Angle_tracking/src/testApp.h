#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
    bool quiet;
    bool debug;
    float angle, distance;
    float preangle, diff;
	ofVec3f ConvertProjectiveToRealWorld(const XnPoint3D& p);
	
	ofxOpenNIContext openni;
	ofxDepthGenerator depth;
	ofxImageGenerator image;
	ofxUserGenerator user;
	ofxOscSender osc;
    
    ofSoundPlayer beat;
    ofTrueTypeFont verdana;
    
    ofVec3f headPosition;
    
};
