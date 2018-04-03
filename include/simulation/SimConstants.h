#ifndef SIMCONSTANTS_H
#define SIMCONSTANTS_H
namespace Simulation {
  // Universe size
  static const float MIN_XY_WORLDPOS = -10000.0f;
  static const float MAX_XY_WORLDPOS =  10000.0f;
  
  // Universe content 
  static const int MAX_WORLDS = 1000;
  static const int MAX_SOLARSYSTEMS = 500;
  static const int MAX_WORLDS_PER_SOLARSYSTEM = 10;
  static const int MIN_WORLDS_PER_SOLARSYSTEM = 2;
  static const int MAX_UNIQUE_NAMES = 1000;

  // Generator
  static const float MIN_SOLARSYSTEM_DISTANCE = 100.0f;

  // Population
  enum Species { Human, Orcish, Elvish, Reptillian };
  static const unsigned int SPECIES_MAX = 4;
  static const long HIGH_POPULATION = 1234908;
  static const long MED_POPULATION  = 125922;
  static const long LOW_POPULATION  = 15312;

  static const long POP_PER_TRADEHUB     = 10000;
  static const long POP_PER_SPACESTATION = 100000;

  // Planet orbits
  static const int ORBIT_BASESIZE = 10;
  static const float ORBIT_BASESPEED = 1.0f;
  static const int ORBIT_INC_X = 5;
  static const int ORBIT_INC_Y = 5;
}
#endif
