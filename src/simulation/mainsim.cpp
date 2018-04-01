#include "mainsim.h"

#include <glm/glm.hpp>

namespace Simulation 
{
  // Constructor
  MainSim::MainSim(void) {
  }
  
  // Destructor
  MainSim::~MainSim(void) {
    delete this->generator;
    delete this->universe;
    delete this->m_mtgen;
  }

  void MainSim::Init(unsigned int seed, int universe_size, int _stepsize) {
    srand(seed); // for rand()
    this->m_mtgen = new std::mt19937(seed);
    this->generator = new Generator(this->m_mtgen);
    this->universe = new Universe(universe_size);
    this->generator->GenerateUniverse(this->universe);

    this->stepsize = _stepsize;
  }

  void MainSim::Update() { 
    this->universe->Update(this->stepsize);
  }

  void DisplayWorld(World* world, unsigned long* maxpop, unsigned long* minpop);

  void MainSim::DisplayWorlds () {
    if (this->universe == NULL) {
      throw ReferencedUninitialisedValueException((char*)"DisplayWorlds was called before universe was initialised");
    }
    unsigned long maxpop = std::numeric_limits<unsigned long>::min();
    unsigned long minpop = std::numeric_limits<unsigned long>::max();
    SolarSystem** solarsystems = this->universe->getSolarSystems();
    World** worlds;
    for (int i=0; i < this->universe->getSolarSystemCount(); i++) {
        worlds = solarsystems[i]->getWorlds(); 
        if (worlds == NULL) {
            throw ReferencedUninitialisedValueException((char*)"DisplayWorlds was called before worlds were initialised");
        }
        glm::vec2 ss_pos = solarsystems[i]->getPosition();
        printf("\nSolar System %d - At position (%d, %d)\n", solarsystems[i]->getID(), static_cast<int>(ss_pos.x), static_cast<int>(ss_pos.y));
        for (int j=0; j < solarsystems[i]->getWorldCount(); j++) {
            DisplayWorld(worlds[j], &maxpop, &minpop);
        }
    }
    
    printf("Lowest population: %lu\nHighest population: %lu\n", minpop, maxpop);
  }

  void DisplayWorld(World* world, unsigned long* maxpop, unsigned long* minpop) {
      printf("World %d: %s\n", world->getID(), world->getName());
      unsigned long* popu = world->getPopulation();
      for (unsigned int i = 0; i < SPECIES_MAX ; i++) {
        if (popu[i] > 0) {
          printf("- %s population:  %lu\n", SpeciesToString(static_cast<Species>(i)),popu[i]);
          if (popu[i] > *maxpop) { *maxpop = popu[i]; }
          if (popu[i] < *minpop) { *minpop = popu[i]; } 
        }
      }
      if (world->getTradehubCount() > 0) 
        printf("- Tradehubs: %d\n- Spacestations: %d\n", world->getTradehubCount(), world->getSpacestationCount());
  }
  
}
