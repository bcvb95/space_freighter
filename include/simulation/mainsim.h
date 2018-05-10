#ifndef MAINSIM_H
#define MAINSIM_H

#include "generator.h"
#include "universe.h"
#include "SimConstants.h"
#include "simutils.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <glm/glm.hpp>

namespace Simulation
{
  enum Resource { Good, Animal, People };
  enum Good     { RawMat, ProcessedMat };
  enum Animal   { Horse, Cow, Dog, Cat };

  class MainSim {
    public:
      MainSim(void);  // Constructor
      ~MainSim(void); // Destructor

      void Init(unsigned int seed, int universe_size);
      void Update(float dt);
      
      Universe* getUniverse() { return this->universe; }
      void DisplayWorlds(bool, int, bool);
    private:
      Generator* generator = NULL;
      Universe* universe = NULL;
      std::mt19937* m_mtgen; // Mersenne Twister Engine for random numbers
  };


}

#endif