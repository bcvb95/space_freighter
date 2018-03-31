#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "world.h"
#include "SimConstants.h"

#include "custom_exceptions.h"

namespace Simulation
{ 

  class Universe {
    public:
      // Members
      Universe(int size);
      ~Universe(void);

      void Init();
      void Update(int step);

      // Getters and setters
      World** getWorlds() { return this->worlds; }
      World* getIthWorld(int i) { return this->worlds[i]; }
      void setIthWorld(int i, World* world) { this->worlds[i] = world; }
      int getSize() { return this->size; }
    private:
      // Properties
      int size;
      World* worlds[MAX_WORLDS] = {NULL};
  };

}

#endif
