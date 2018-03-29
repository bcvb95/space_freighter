#ifndef SIMUTILS_H
#define SIMUTILS_H

#include "custom_exceptions.h"
#include "SimConstants.h"

namespace Simulation {
  void RandomUniqueIntegers (int, int, int, int[]);
  const char* SpeciesToString (Species species);
}

#endif
