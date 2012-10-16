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
	ofSetVerticalSync(false);
	kinect.init(false, false);  // disable infrared/rgb video iamge (faster fps) ...we are using depth
	kinect.open();
    forepoint = ofVec3f (0, 0, 0);
    lastPoint = ofVec3f (0, 0, 0);
    secondPoint = ofVec3f (0, 0, 0);
    drawCloud = true;
    drawCopy = false;
    doDrawing = true;
 
    drawing.setMode(OF_PRIMITIVE_LINE_STRIP);
    drawing2.setMode(OF_PRIMITIVE_LINE_STRIP);
    meshCopy.setMode(OF_PRIMITIVE_LINE_STRIP);
    ofSetLineWidth(0.8);
}

void testApp::update() {
	kinect.update();
}

void testApp::draw() {
	ofBackground(245);
    ofSetColor(255);  //everything drawn with white tint
	kinect.drawDepth(0, 0);
	easyCam.begin();
    
    ofScale(1, -1, -1);
    //ofTranslate(0, 0, -200);
    
   

    ofSetColor(0);
	int width = kinect.getWidth();
	int height = kinect.getHeight();
	
	float* distancePixels = kinect.getDistancePixels(); 
    ofMesh cloud;
    cloud.setMode(OF_PRIMITIVE_POINTS);

    float minZ = 1500;
    float minX = 0;
    float minY = 0;
    float dist = 1500;
    float secondZ = 1500;
    float secondX = 0;
    float secondY = 0;
    
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int i = y * width + x;
			float z = distancePixels[i];
            
            if(z !=0 && z < 1500 && drawCloud == true) cloud.addVertex(ConvertProjectiveToRealWorld(x, y, z));
			
            if(z != 0 && z < minZ) {
                minZ= z;
                minX = x;
                minY = y;
                forepoint = ConvertProjectiveToRealWorld(minX, minY, minZ);
			}
            else if ( z !=0 && z > minZ && z-minZ < dist) {
                dist = z - minZ;
                secondZ = z;
                secondX = x;
                secondY = y;
                
            }
		}
	}
    if(drawCloud) cloud.draw();
    
    //secondPoint = ConvertProjectiveToRealWorld(secondX, secondY, secondZ);

    ofSetColor(50);
    if(doDrawing) {
        drawing.addVertex(forepoint);
        //drawing2.addVertex(secondPoint);
    }
    //drawing.draw();
    //drawing2.draw();
    
   
    //ofCircle(secondPoint.x, secondPoint.y, 5);
    
    if(drawCopy) {
        meshCopy.draw();
    }
        
    easyCam.end();
    
    //averaging the data in a region around the forepoint
    ofNoFill();
    int searchRadius = 64;
    int searchDistance = 100;
    int count = 0;
    ofVec3f sum = ofVec3f(0, 0, 0);

    ofRect(minX-searchRadius/2, minY+searchRadius/2, searchRadius, searchRadius);
    for(int x = -searchRadius/2; x < searchRadius/2; x++) {
        for (int y = -searchRadius/2; y < searchRadius/2; y++) {
            int curx = x+minX;
            int cury = y+ minY;
            if( curx < width && curx >0 && y + cury >0 && cury < height) {
                int i = cury*width + curx;
                float z = distancePixels[i];
                if(z!=0 && z-minZ < searchDistance) {
                    sum.x+= curx;
                    sum.y+= cury;
                    //unlike x and y, z is taken from distancePixels[i] so dont adjust for current (x, y) like curx cury
                    sum.z+= z;
                    count++;
                }
            }
        }
    }
    
    //we are only looking at a single point. no perspective issue involed?
    //ofVec3f avg = ConvertProjectiveToRealWorld(sum.x/count, sum.y/count, sum.z/count);
    
    ofSetColor(0, 255, 0);
    ofFill();
    ofCircle(avg.x, avg.y, 5);
    ofSetColor(255, 0, 0);
    ofFill();
    ofCircle(forepoint.x, forepoint.y, 5);
    
    ofSetColor(0);
    ofDrawBitmapString( "space bar to render / t to resume", 50, 100);
    ofDrawBitmapString( ofToString(forepoint.x) + "/" + ofToString(avg.x), 50, 150);
}

void testApp::exit() {
	kinect.close();
}

void testApp::keyPressed(int key) {
	if(key == ' ') {
        meshCopy.addVertices(drawing.getVertices());
        drawCopy = true;
        doDrawing = false;
        drawCloud = false;
        drawing.clear();
    }
    
    if (key == 't') {
        drawCopy = false;
        doDrawing = true;
        drawCloud = true;
    }
}
