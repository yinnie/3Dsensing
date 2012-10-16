#include "testApp.h"

void testApp::setup() {
	ofSetVerticalSync(true);
	openni.setup();
	image.setup(&openni);
	depth.setup(&openni);
    user.setup(&openni);
	openni.registerViewport();
	openni.setMirror(true);
    angle = 0;
}

void testApp::update(){
	openni.update();
	image.update();
	depth.update();
    user.update();
    
    ofxTrackedUser* tracked = user.getTrackedUser(1);
    
    if(tracked != NULL) {        
        XnPoint3D  armupper1= tracked->right_upper_arm.position[0];
        XnPoint3D armupper2 = tracked->right_upper_arm.position[1];
        XnPoint3D armlower2 = tracked->right_lower_arm.position[1];
        
        //Using depth generator will give me bad access error..?????????
        //depth_generator.ConvertRealWorldToProjective(1, &start, &start);
        
        ofVec3f p1 = ofVec3f(armupper1.X, armupper1.Y, armupper1.Z);
        ofVec3f p2 = ofVec3f(armupper2.X, armupper2.Y, armupper2.Z);
        ofVec3f p3 = ofVec3f(armlower2.X, armlower2.Y, armlower2.Z);
        ofVec3f v1 = p2 - p1;
        ofVec3f v2 = p3 - p2;
        angle = v1.angle(v2);
    }

}

void testApp::draw(){
	ofBackground(0);
	//ofSetColor(255);
    ofPushMatrix();
	ofScale(.75, .75, .75);
	depth.draw(0, 0, 640, 480);
    //user.draw();
    
    ofxTrackedUser* tracked = user.getTrackedUser(1);
    
    if(tracked != NULL) {
        tracked->right_upper_arm.debugDraw();
        tracked->right_lower_arm.debugDraw();
    }
    ofPopMatrix();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(angle), 650, 300);
    
    cout<< angle << endl;
}
