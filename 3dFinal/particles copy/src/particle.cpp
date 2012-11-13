#include "particle.h"


void Particle::update() {
    vel += force;
    pos += vel;
    life -= 1;
    
}

void Particle::draw() {
    float c = ofMap(life, 0, 500, 0, 255);
    ofSetColor(c);
    ofFill();
    float s = ofMap(life, 0, 500, 0.1, 0.7);
    ofCircle(pos.x, pos.y, pos.z, s);
}

bool Particle::isDead() {
    if (life < 0.0) {
        return true;
    } else {
        return false;
    }
}

void Particle::addforce(ofVec3f f) {
    force = f;
    
}