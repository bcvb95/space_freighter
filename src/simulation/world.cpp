#include "world.h"
#include <string.h>
#include <stdlib.h>

namespace Simulation {
  
  World::World (int _ID) {
    this->ID = _ID;
  }

  World::~World() {
    free((void*)this->name);
  }

  void World::Init(const unsigned char* _name, unsigned long long _popu_count[],
                   unsigned int _tradehub_count, unsigned int _spacestation_count) 
  {
    this->name = _name;
    memcpy(this->popu_count, _popu_count, sizeof(unsigned int)*SPECIES_MAX);
    this->tradehub_count = _tradehub_count;
    this->spacestation_count = _spacestation_count;
  }

}
