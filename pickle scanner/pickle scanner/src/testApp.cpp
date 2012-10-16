#include "testApp.h"


void testApp::setup(){
     
    ofBuffer buffer = ofBufferFromFile("data1.txt");
    string import = buffer.getText();
    
    vector<string> stuff = ofSplitString(import, "\n");
    n = stuff.size();

    raw.resize(n);  //initiate raw (a vector) using resize
    
    for(int i = 0; i<n; i++) {
        vector<string> split = ofSplitString(stuff[i], ",");
        raw[i] = ofPoint(ofToFloat(split[0]), ofToFloat(split[1]), ofToFloat(split[2]));
    }
   
    ofBackground(255);
}


void testApp::update(){

}

void testApp::draw(){

    
    cam.begin();
    ofSetColor(0, 0, 0);
    ofFill();
    ofScale(10, 10, 10);
    ofMesh mesh;
     for (int i = 0; i<n; i++) {
         mesh.addVertex(raw[i]);
     }
    mesh.draw();
    cam.end();
}
