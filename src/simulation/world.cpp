#include "world.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "simutils.h"

namespace Simulation {
  
  World::World (int _ID) {
    this->ID = _ID;
  }

  World::~World() {
    free((void*)this->name);
  }

  void World::Init(const unsigned char* _name, unsigned long _popu_count[],
                   unsigned int _tradehub_count, unsigned int _spacestation_count) 
  {
    this->name = _name;
    for (int i=0; i < SPECIES_MAX; i++) {
      this->popu_count[i] = _popu_count[i];
    }
    this->tradehub_count = _tradehub_count;
    this->spacestation_count = _spacestation_count;
  }

  void World::Update(int stepsize) {
    
  }

}
