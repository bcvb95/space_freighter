#ifndef SIMUTILS_H
#define SIMUTILS_H

#include "custom_exceptions.h"
#include "SimConstants.h"
#include <glm/glm.hpp>

namespace Simulation {
  float Vector2Dist (glm::vec2, glm::vec2);
  void RandomUniqueIntegers (int, int, int, int[]);
  const char* SpeciesToString (Species species);
}

#endif
