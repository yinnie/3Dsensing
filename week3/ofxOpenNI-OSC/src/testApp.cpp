#include "testApp.h"

ofVec3f testApp::ConvertProjectiveToRealWorld(const XnPoint3D& p) {
	XnPoint3D world;
	depth.getXnDepthGenerator().ConvertProjectiveToRealWorld(1, &p, &world);
	return ofVec3f(world.X, world.Y, world.Z);
}

void testApp::setup() {
	ofSetVerticalSync(true);
	openni.setup();
	image.setup(&openni);
	depth.setup(&openni);
	user.setup(&openni);
	openni.registerViewport();
	openni.setMirror(true);

	osc.setup("localhost", 8000);
	distance = 0;
	angle = 0;
    preangle = 0;
    diff = 0;
    quiet = false;
    debug = true;
    beat.loadSound("sounds/1085.mp3");
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 28);
}

void testApp::update(){
    
	openni.update();
	image.update();
	//depth.update();
	user.update();
    
    ofSoundUpdate();
    
    ofxTrackedUser* tracked = user.getTrackedUser(1);
    
    if(tracked != NULL) {
        XnPoint3D armupper1 = tracked->right_upper_arm.position[0];
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
        
        diff = angle - preangle;
        if(angle > 30){
            beat.play();
            quiet = true;
        }
        if(angle < 30) {
            quiet = false;
        }
        
        preangle = angle;
        ofxOscMessage msg;
		msg.setAddress("/angle");
		msg.addFloatArg(ofMap(angle, 10, 180, 0, 1));
		osc.sendMessage(msg);
    }
     
    if(user.getNumberOfTrackedUsers() > 0) {
		ofxTrackedUser* cur = user.getTrackedUser(1); // old API starts users at 1, not 0
		ofVec3f leftHand = ConvertProjectiveToRealWorld(cur->left_lower_arm.position[1]);
		ofVec3f rightHand = ConvertProjectiveToRealWorld(cur->right_lower_arm.position[1]);
		
		distance = leftHand.distance(rightHand);
		
		ofxOscMessage msg;
		msg.setAddress("/distance");
		msg.addFloatArg(ofMap(distance, 10, 1000, 0, 1));
		osc.sendMessage(msg);
	}
     
}

void testApp::draw(){
    ofBackground(0);
	ofSetColor(255);
    ofPushMatrix();
	ofScale(.75, .75, .75);
	image.draw(0, 0, 640, 480);
    //user.draw();
    
    ofxTrackedUser* tracked = user.getTrackedUser(1);
        
    if(debug) {
    if(tracked != NULL) {
        tracked->right_upper_arm.debugDraw();
        tracked->right_lower_arm.debugDraw();
    }
    }
    if(quiet) {
        ofSetColor(255, 255, 0);
        verdana.drawString("NOT", 650, 200);
    }
      else {
          ofSetColor(255, 255, 0);
        verdana.drawString("DIGGING", 650, 200);
    }
    ofPopMatrix();
    
    if (debug) {
    ofSetColor(255);
    verdana.drawString("angle" + ofToString(angle), 650, 300);
    verdana.drawString("diff" + ofToString(diff), 650, 350);
    }
    
    
    cout<< angle << endl;

}