#pragma once
#include "ofMain.h"
#include "particle.h"
#include <vector>


class particleSystem {

public:
	particleSystem() {}
	particleSystem (int num, ofVec3f v){
        origin = v;
        particles.resize(num);
        for(int i =0; i<num; i++) {
            Particle* p = new Particle(v);
            particles.push_back(*p);
        }        
    }
    
	void update();
    void draw();
    void addParticle();
    bool dead();
    void addforce(ofVec3f f);
	
	vector<Particle> particles;
	ofVec3f origin;

};


