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

	osc.setup("localhost", 3333);
	distance = 0;
	angle = 0;
    preangle = 0;
    diff = 0;
    quiet = false;
    debug = true;
    beat.loadSound("sounds/1085.mp3");
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 28);
    
    headPosition = ofVec3f(0, 0, 0);
}

void testApp::update(){
    
	openni.update();
	image.update();
	//depth.update();
	user.update();
    
    ofSoundUpdate();
    
    ofxTrackedUser* tracked = user.getTrackedUser(1);
    
    if(tracked != NULL) {
        XnPoint3D legupper1 = tracked->right_upper_leg.position[0];
        XnPoint3D legupper2 = tracked->right_upper_leg.position[1];
        XnPoint3D leglower2 = tracked->right_lower_leg.position[1];
        XnPoint3D head = tracked->neck.position[0];

        headPosition = ofVec3f(head.X, head.Y, head.Z);
        //Using depth generator will give me bad access error..?????????
        //depth_generator.ConvertRealWorldToProjective(1, &start, &start);
        
        ofVec3f p1 = ofVec3f(legupper1.X, legupper1.Y, legupper1.Z);
        ofVec3f p2 = ofVec3f(legupper2.X, legupper2.Y, legupper2.Z);
        ofVec3f p3 = ofVec3f(leglower2.X, leglower2.Y, leglower2.Z);
        ofVec3f v1 = p2 - p1;
        ofVec3f v2 = p3 - p2;
        angle = v1.angle(v2);

        ofxOscMessage msg;
        msg.setAddress("/angle");
        if(angle >= 120) { msg.addFloatArg(1.0); }
        else { msg.addFloatArg(0.0);}
        
        //msg.addFloatArg(headPosition.x);
        msg.addFloatArg(headPosition.y);
        msg.addFloatArg(headPosition.z);
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
        tracked->right_upper_leg.debugDraw();
        tracked->right_lower_leg.debugDraw();
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
        verdana.drawString("head" + ofToString(headPosition), 650, 200);
    }

}