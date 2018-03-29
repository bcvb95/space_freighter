#ifndef SIMCONSTANTS_H
#define SIMCONSTANTS_H
namespace Simulation {
  // Universe size
  static const int MAX_WORLDS = 1000;
  static const int MAX_UNIQUE_NAMES = 1000;

  // Population
  enum Species { Human, Orcish, Elvish, Reptillian };
  static const unsigned int SPECIES_MAX = 4;
  static const long double HIGH_POPULATION = 1000;
  static const long double MED_POPULATION  = 100;
  static const long double LOW_POPULATION  = 100;
}
#endif
