#include "particleSystem.h"


void particleSystem::update() {
    
    vector<Particle>::iterator it;
    
	for (it = particles.begin(); it < particles.end(); it++) {
        if(it->isDead()) {
            it = particles.erase(it);
        } else {
            it->update();

        }
    }
    
    if(particles.size() > 2) {
        particles.pop_back();
    }
}

void particleSystem::addforce(ofVec3f f) {
    
    vector<Particle>::iterator it;
    
	for (it = particles.begin(); it < particles.end(); it++) {
        it->addforce(f);
    }
    
}

void particleSystem::draw() {
    
    vector<Particle>::iterator it;
    
	for (it = particles.begin(); it < particles.end(); it++) {
        if(it->isDead()) {
            it = particles.erase(it);
        } else {
            it->draw();
        }
    }

    
}

/*  this wont work!!!  why? 
 
 
    for(int i = 0; i< particles.size(); i++) {
        particles[i].update();
        particles[i].draw();
        if (particles[i].isDead()) {
            particles[i] = particles.erase(particles[i]);
        }
    }

}
 
 */

void particleSystem:: addParticle() {
    Particle* p = new Particle(origin);
    particles.push_back(*p);
    
    if(particles.size() > 4) {
        particles.pop_back();
    }
    
}






