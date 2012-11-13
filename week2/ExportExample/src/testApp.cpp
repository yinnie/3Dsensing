#include "testApp.h"


void testApp::setup() {
	kinect.init();
	kinect.setRegistration(true); //keeps the depth image aligned with color image
    //covert the info between this range to color data
    //below set the range...but we still have access to data outside of range
	kinect.setDepthClipping(500, 1000);  //real world..50cm to 1.5meters
	kinect.open();
}

void testApp::update() {
	kinect.update();
	if(kinect.isFrameNew()) {  //if we dont have isFrameNew..app will run slower..
		if(ofGetKeyPressed(' ')) {
			ofPixels& depthPixels = kinect.getDepthPixelsRef();  //"&" i dont want to copy the data..just reference it
			ofPixels& colorPixels = kinect.getPixelsRef();
			ofSaveImage(depthPixels, "depth.png");
			ofSaveImage(colorPixels, "color.png");
			img.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);  //using alpha channel to store depth data
			for(int y = 0; y < 480; y++) {
				for(int x = 0; x < 640; x++) {
					ofColor color = colorPixels.getColor(x, y);
					ofColor depth = depthPixels.getColor(x, y);
					img.setColor(x, y, ofColor(color, depth.getBrightness()));
				}
			}
			img.saveImage("9.png");
		}
	}
}

void testApp::draw() {
	ofBackground(0);
	ofSetColor(255, 255, 255);
	kinect.drawDepth(0, 0, 640, 480);
	kinect.draw(0, 480, 640, 512);
}

void testApp::exit() {
	kinect.close();
}

