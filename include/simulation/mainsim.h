#ifndef MAINSIM_H
#define MAINSIM_H

#include "universe.h"
#include "SimConstants.h"
#include "simutils.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>

namespace Simulation
{
  enum Resource { Good, Animal, People };
  enum Good     { RawMat, ProcessedMat };
  enum Animal   { Horse, Cow, Dog, Cat };

  class MainSim {
    public:
      MainSim(void);  // Constructor
      ~MainSim(void); // Destructor

      void Init(unsigned int seed);

      void DisplayWorlds();
    private:
      Universe* universe;
      std::mt19937* m_mtgen; // Mersenne Twister Engine for random numbers
  };


}

#endif
