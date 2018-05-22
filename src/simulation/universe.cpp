#include "universe.h"

namespace Simulation {

  Universe::Universe(int _world_count) {
     if (_world_count > MAX_WORLDS) {
      throw IllegalUniverseSizeException();
      return;
    }
    this->world_count = _world_count;
    if (MAX_WORLDS > MAX_UNIQUE_NAMES) {
      throw IllegalMaxWorldsException();
    }
  }


  Universe::~Universe() {
    for (int i = 0; i < this->solar_system_count; i++) {
      delete this->solar_systems[i];
    }
  }

  void Universe::Init() {
   
  }

  void Universe::Update(float dt) {
    for (int i = 0; i < this->solar_system_count; i++) {
      solar_systems[i]->Update(dt);
    }
  }

  void Universe::AddSolarSystem (SolarSystem* solarsystem) { 
    if (this->solar_system_count+1 > MAX_SOLARSYSTEMS) {
      throw ValueExceedsMaximumException((char*) "More solar systems generated than maximum.");
    }
    this->solar_systems[this->solar_system_count] = solarsystem;
    this->solar_system_count++;
  }

  SolarSystem* Universe::getSolarSystemByID (int id) {
    for (int i=0; i < this->solar_system_count; i++) {
      if (this->solar_systems[i]->getID() == id) {
        return this->solar_systems[i];
      }
    }
  }
  World* Universe::getWorldByID (int id) {
    for (int i=0; i < this->world_count; i++) {
      if (this->worlds[i]->getID() == id) {
        return this->worlds[i];
      }
    }
  }
}
