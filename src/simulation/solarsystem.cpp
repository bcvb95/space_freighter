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
        if (this->world_count == 0) {
            throw ReferencedUninitialisedValueException((char*) "Called Solar System Init before adding any worlds.");
        }
        this->position = _position;
        // Put planets in orbit
        int orbit_layer = 1;
        for (int i=0; i < this->world_count; i++) {
            orbit_layer += rand() % 5;
            this->worlds[i]->SetOrbit(orbit_layer, ORBIT_BASESPEED, rand()%360, &this->position);
        }
    }

    void SolarSystem::Update(int dt) {
        for (int i=0; i < this->world_count; i++) {
            worlds[i]->Update(dt);
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