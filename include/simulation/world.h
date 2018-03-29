#ifndef WORLD_H
#define WORLD_H

#include "SimConstants.h"

namespace Simulation {
  

  class World {
    public:
      World(int);
      ~World(void);

      void Init(const unsigned char*, unsigned long long[], unsigned int, unsigned int);

      int getID() { return this->ID; }
      char* getName() { return (char*)this->name; }
      unsigned long long* getPopulation() { return popu_count; }
    private:
      int ID;
      const unsigned char* name;
      unsigned long long popu_count[SPECIES_MAX];
      unsigned int tradehub_count;
      unsigned int spacestation_count;
  };

}

#endif
