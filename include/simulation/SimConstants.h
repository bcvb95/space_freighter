#ifndef SIMCONSTANTS_H
#define SIMCONSTANTS_H
namespace Simulation {
  // Universe size
  static const int MAX_WORLDS = 1000;
  static const int MAX_UNIQUE_NAMES = 1000;

  // Population
  enum Species { Human, Orcish, Elvish, Reptillian };
  static const unsigned int SPECIES_MAX = 4;
  static const long HIGH_POPULATION = 1234908;
  static const long MED_POPULATION  = 125922;
  static const long LOW_POPULATION  = 15312;

  static const long POP_PER_TRADEHUB     = 100000;
  static const long POP_PER_SPACESTATION = 100000000;
}
#endif
