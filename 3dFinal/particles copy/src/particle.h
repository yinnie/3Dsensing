#pragma once
#include "ofMain.h"


class Particle {
public:
    float life;
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f force;
    
    Particle() {}
    Particle(ofVec3f origin) {
        pos = origin;
        force = ofVec3f (0, 0.001, 0);
        vel = ofVec3f (0, ofRandom(-2,0), 0);
        life = 500.0;
    }
    
    void update();
    void draw();
    bool isDead();
    void addforce(ofVec3f f);
    
  
    
};
