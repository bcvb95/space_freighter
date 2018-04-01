#include "solarsystem.h"

namespace Simulation {
    SolarSystem::SolarSystem(int _ID) {
        this->ID = _ID;
    }

    SolarSystem::~SolarSystem() {
        for (int i = 0; i < this->world_count; i++) {
            delete this->worlds[i];
        }   
    }

    void SolarSystem::Init(glm::vec2 _position) {
        this->position = _position;
    }

    void SolarSystem::Update(int stepsize) {
        for (int i=0; i < this->world_count; i++) {
            worlds[i]->Update(stepsize);
        }
    }
    
    void SolarSystem::AddWorld(World* newworld) {
        if (this->world_count+1 > MAX_WORLDS_PER_SOLARSYSTEM) {
            throw ValueExceedsMaximumException((char*) "More worlds than maximum in solar system " + this->ID);
        }
        this->worlds[this->world_count] = newworld;
        this->world_count++;
    }
}