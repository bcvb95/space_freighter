#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "solarsystem.h"
#include "SimConstants.h"

#include "custom_exceptions.h"

namespace Simulation
{ 

  class Universe {
    public:
      // Members
      Universe(int world_count);
      ~Universe(void);

      void Init();
      void Update(int dt);

      void AddSolarSystem (SolarSystem* solarsystem); 

      // Getters and setters
      
      
      SolarSystem** getSolarSystems() { return this->solar_systems; }
      SolarSystem* getIthSolarSystem(int i) { return this->solar_systems[i]; }
      SolarSystem* getSolarSystemByID(int id);

      World** getWorlds() { return this->worlds; }
      World* getIthWorld(int i) { return this->worlds[i]; }
      World* getWorldByID(int id);

      void setIthWorld(int i, World* world) { this->worlds[i] = world; }
      int getWorldCount() { return this->world_count; }
      int getSolarSystemCount() { return this->solar_system_count; }
      
    private:
      // Properties
      int world_count;
      int solar_system_count = 0;
      
      World* worlds[MAX_WORLDS] = {NULL};
      SolarSystem* solar_systems[MAX_SOLARSYSTEMS] = {NULL};
  };

}

#endif
