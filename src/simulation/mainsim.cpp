#include "mainsim.h"

namespace Simulation 
{
  // Constructor
  MainSim::MainSim(void) {
    std::cout << "Constructing main simulation." << std::endl; 
    universe = new Universe();
  }
  
  // Destructor
  MainSim::~MainSim(void) {
    std::cout << "Destructing main simulation." << std::endl;
    delete universe;
  }

  void MainSim::Init(unsigned int seed) {
    srand(seed);
    this->m_mtgen = new std::mt19937(seed);
    this->universe->Init(949, this->m_mtgen);
  }

  void MainSim::DisplayWorlds () {
    World** worlds = this->universe->getWorlds();
    unsigned long long maxpop = std::numeric_limits<unsigned long long>::min();
    unsigned long long minpop = std::numeric_limits<unsigned long long>::max();
    for (int i=0; i < this->universe->getSize(); i++) {
      printf("World %d: %s\n", worlds[i]->getID(), worlds[i]->getName());
      unsigned long long* pop = worlds[i]->getPopulation();
      for (unsigned int i = 0; i < SPECIES_MAX ; i++) {
        if (pop[i] > 0) {
          printf("- %s population:  %llu\n", SpeciesToString(static_cast<Species>(i)), pop[i]);
          if (pop[i] > maxpop) { maxpop = pop[i]; }
          if (pop[i] < minpop) { minpop = pop[i]; }
        }
      }
    }
    printf("Lowest population: %llu\nHighest population: %llu\n", minpop, maxpop);
  }
  
}
