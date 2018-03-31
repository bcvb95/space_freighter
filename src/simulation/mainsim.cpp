#include "mainsim.h"

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

  void MainSim::DisplayWorlds () {
    if (this->universe == NULL) {
      throw ReferencedUninitialisedValueException((char*)"DisplayWorlds was called before universe was initialised");
    }
    World** worlds = this->universe->getWorlds();
    if (worlds == NULL) {
      throw ReferencedUninitialisedValueException((char*)"DisplayWorlds was called before worlds were initialised");
    }
    unsigned long maxpop = std::numeric_limits<unsigned long>::min();
    unsigned long minpop = std::numeric_limits<unsigned long>::max();
    for (int i=0; i < this->universe->getSize(); i++) {
      printf("World %d: %s\n", worlds[i]->getID(), worlds[i]->getName());
      unsigned long* popu = worlds[i]->getPopulation();
      for (unsigned int i = 0; i < SPECIES_MAX ; i++) {
        if (popu[i] > 0) {
          printf("- %s population:  %lu\n", SpeciesToString(static_cast<Species>(i)),popu[i]);
          if (popu[i] > maxpop) { maxpop = popu[i]; }
          if (popu[i] < minpop) { minpop = popu[i]; }
        }
      }
      if (worlds[i]->getTradehubCount() > 0) 
        printf("Tradehubs: %d\nSpacestations: %d\n", worlds[i]->getTradehubCount(), worlds[i]->getSpacestationCount());
    }
    printf("Lowest population: %lu\nHighest population: %lu\n", minpop, maxpop);
  }
  
}
