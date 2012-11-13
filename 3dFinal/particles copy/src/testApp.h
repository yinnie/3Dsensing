#pragma once

#include "ofMain.h"
#include "particleSystem.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyPressed(int key);
    void makeMesh(ofImage mimg);
	
    float xforce;
    float yforce;
    float zforce;
    
	ofEasyCam cam;
	ofMesh mesh;
    int counter;
    vector<particleSystem> systems;

    ofVec3f mforce;
    ofImage img;
};
