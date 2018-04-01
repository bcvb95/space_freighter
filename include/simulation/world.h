#ifndef WORLD_H
#define WORLD_H

#include <stdlib.h>
#include <glm/glm.hpp>
#include "SimConstants.h"

namespace Simulation {
  

  class World {
    public:
      World(int, int);
      ~World(void);

      void Init(const unsigned char*, unsigned long[], unsigned int, unsigned int);
      void Update(int step);

      int getID() { return this->ID; }
      char* getName() { return (char*)this->name; }
      unsigned long* getPopulation() { return this->popu_count; }
      unsigned int getTradehubCount() { return this->tradehub_count; }
      unsigned int getSpacestationCount() { return this->spacestation_count; }
    private:
      int ID;
      int solar_system_ID;
      const unsigned char* name = 0;
      unsigned long popu_count[SPECIES_MAX] = {0};
      unsigned int tradehub_count;
      unsigned int spacestation_count;

      // orbit in system
      glm::vec2 orbit_radius;
      glm::vec2 orbit_position;
      int speed;
  };

}

#endif
