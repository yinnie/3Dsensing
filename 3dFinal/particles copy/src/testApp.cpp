#include "testApp.h"

void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
}

void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

ofVec3f getVertexFromImg(ofImage& img, int x, int y) {
	ofColor color = img.getColor(x, y);
	if(color.a > 0) {
		float z = ofMap(color.a, 0, 255, -160, 160);
		return ofVec3f(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
	} else {
		return ofVec3f(0, 0, 0);
	}
}


void testApp::setup(){
    
    ofSetVerticalSync(true);
    counter = 1;
	img.loadImage("1.png");
	
	mesh.setMode(OF_PRIMITIVE_POINTS);
   	int skip = 5;
	int width = img.getWidth();
	int height = img.getHeight();
	ofVec3f zero(0, 0, 0);
	for(int y = 0; y < height - skip; y += skip) {
		for(int x = 0; x < width - skip; x += skip) {
			ofVec3f nw = getVertexFromImg(img, x, y);
            
            if(nw != 0) {
            particleSystem ps = particleSystem(1, nw);
            systems.push_back(ps);
            }
        }
	}
    
	glEnable(GL_DEPTH_TEST);
    
    mforce = ofVec3f (0, 0, 0);
    xforce = 0;
    yforce = 0;
    zforce = 0;
    
    ofHideCursor();
    
}

void testApp::makeMesh(ofImage mimg) {
    int skip = 5;
	int width = mimg.getWidth();
	int height = mimg.getHeight();
	ofVec3f zero(0, 0, 0);
	for(int y = 0; y < height - skip; y += skip) {
		for(int x = 0; x < width - skip; x += skip) {
			ofVec3f nw = getVertexFromImg(mimg, x, y);
            
            if(nw != 0) {
                particleSystem ps = particleSystem(1, nw);
                systems.push_back(ps);
            }
        }
	}
}

void testApp::update(){
    
    mforce = ofVec3f(xforce, yforce, zforce);
    for(int i = 0; i < systems.size(); i++) {
	    systems[i].update();
        systems[i].addforce(mforce);
        //systems[i].addParticle();
    }
    mforce = ofVec3f(0, 0, 0);
}

void testApp::draw(){
	ofBackground(0);
    ofSetColor(100,10);
    cam.begin();
	ofScale(1, -1, 1); // make y point down
	//mesh.draw();

    for(int i = 0; i < systems.size(); i++) {
	    systems[i].draw();
    }

    cam.end();

	//ofDrawBitmapString("fps " + ofToString(ofGetFrameRate(), 2)
     //                 + " | useVA " + ofToString(va), 20,20);	
}


void testApp::keyPressed(int key) {
    switch (key) {
        case 's':
            yforce += 0.001;
            break;
        case 'w':
            yforce -= 0.001;
        case 'a':
            xforce -= 0.001;
        case 'd':
            xforce += 0.001;
        case 'q':
            zforce += 0.001;
        case ' ':
            for(int i = 0; i < systems.size(); i++) {
                systems[i].addParticle();
            }
        case 'n':
            counter++;
            img.loadImage(ofToString(counter) + ".png");
            makeMesh(img);
            
        default:
            break;
    }
    
}


