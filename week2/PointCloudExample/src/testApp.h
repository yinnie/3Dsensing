#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	
	ofxKinect kinect;
	ofEasyCam easyCam;
	bool useProjective;
    
    //you dont wan to just use brightness as Z of the points..
    //what you want to do is to project it..projection...your hand stays same size no matter where you put it
};
