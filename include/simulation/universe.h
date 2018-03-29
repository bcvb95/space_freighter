#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <random>
#include "world.h"
#include "SimConstants.h"
#include "simutils.h"
#include "custom_exceptions.h"

namespace Simulation
{ 

  class Universe {
    public:
      // Members
      Universe(void);
      ~Universe(void);

      void Init(int size, std::mt19937*);
      World** getWorlds() { return this->worlds; }
      int getSize() { return this->size; }
    private:
      // Members
      void GenerateAllWorlds();
      void GenerateWorld(World*, int, unsigned long long);
      char* GetUniqueWorldName();
      int CheckDuplicateNames(char*);
      void LoadWorldNames();
      // Properties
      World* worlds[MAX_WORLDS];
      int size;
      std::mt19937* m_mtgen;
      char* possible_world_names[MAX_UNIQUE_NAMES];
      unsigned int namecount;
  };

}

#endif
