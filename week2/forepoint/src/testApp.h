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
	
    bool drawCloud, drawCopy, doDrawing;
    ofVec3f forepoint;
    ofVec3f lastPoint;
    ofVec3f secondPoint;
	ofxKinect kinect;
	ofEasyCam easyCam;
    ofMesh drawing;
    ofMesh drawing2;
    ofMesh meshCopy; //copy of drawing
	
    
};
