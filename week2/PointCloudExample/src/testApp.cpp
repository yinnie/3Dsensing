#include "testApp.h"

const float FovX = 1.0144686707507438;
const float FovY = 0.78980943449644714;
const float XtoZ = tanf(FovX / 2) * 2;
const float YtoZ = tanf(FovY / 2) * 2;
const unsigned int Xres = 640;
const unsigned int Yres = 480;

ofVec3f ConvertProjectiveToRealWorld(float x, float y, float z) {
	return ofVec3f((x / Xres - .5f) * z * XtoZ,
								 (y / Yres - .5f) * z * YtoZ,
								 z);
}

void testApp::setup() {
	ofSetVerticalSync(true);
	kinect.init(false, false);  // disable infrared/rgb video iamge (faster fps) ...we are using depth
	kinect.open();
	useProjective = true;
}

void testApp::update() {
	kinect.update();
}

void testApp::draw() {
	ofBackground(0);
	
	ofSetColor(255);  //everything drawn with white tint
	kinect.drawDepth(0, 0, 400, 300);
	
	easyCam.begin();  
	int width = kinect.getWidth();
	int height = kinect.getHeight();
	ofScale(1, -1, -1); // orient the point cloud properly ..data from kinect is in a diff coordinate sys then OF world
	if(useProjective) {
		ofTranslate(-width / 2, -height / 2); // center the projective point cloud
	} else {
		ofTranslate(0, 0, -1500); // rotate about z = 1500 mm
	}
	float* distancePixels = kinect.getDistancePixels(); // distance in millimeters
    //use pointer here..becoz we want a description of where this array of values are..the first one..
    //this allows you to index ..with offset fro first value..
    
	ofMesh cloud;  //mesh is like...prepare a bunch of points lines.etc..and draw all at once..
	cloud.setMode(OF_PRIMITIVE_POINTS);
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int i = y * width + x;
			float z = distancePixels[i];
            //if we were using ofpixels ..it will be like pixels.get()..
			if(z != 0) { // ignore empty depth pixels
				if(useProjective) {
					cloud.addVertex(ofVec3f(x, y, z));
                    
                    //but
                    //you dont wan to just use brightness as Z of the points..
                    //what you want to do is to project it..projection...your hand stays same size no matter where you put it
				} else {
					cloud.addVertex(ConvertProjectiveToRealWorld(x, y, z));
				}
			}
		}
	}
	cloud.drawVertices();
	easyCam.end();
	
	ofSetColor(255);
	ofDrawBitmapString(useProjective ? "projective point cloud" : "real world point cloud", 10, 20);
}

void testApp::exit() {
	kinect.close();
}

void testApp::keyPressed(int key) {
	if(key == ' ') {
		useProjective = !useProjective;
	}
}