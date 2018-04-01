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

  void MainSim::Init(unsigned int seed, int universe_size, int _delta_time) {
    srand(seed); // for rand()
    this->m_mtgen = new std::mt19937(seed);
    this->generator = new Generator(this->m_mtgen);
    this->universe = new Universe(universe_size);
    this->generator->GenerateUniverse(this->universe);

    this->delta_time = _delta_time;
  }

  void MainSim::Update() { 
    this->universe->Update(this->delta_time);
  }

  void DisplayWorld(World* world, unsigned long* maxpop, unsigned long* minpop);

  void MainSim::DisplayWorlds (bool pop_flag, int steps, bool pos_flag) {
    if (this->universe == NULL) {
      throw ReferencedUninitialisedValueException((char*)"DisplayWorlds was called before universe was initialised");
    }
    unsigned long maxpop = std::numeric_limits<unsigned long>::min();
    unsigned long minpop = std::numeric_limits<unsigned long>::max();
    SolarSystem** solarsystems = this->universe->getSolarSystems();
    World** worlds;
    int stepcount = 0;
    char input[10];
    for (int i=0; i < this->universe->getSolarSystemCount(); i++) {
        worlds = solarsystems[i]->getWorlds(); 
        if (worlds == NULL) {
            throw ReferencedUninitialisedValueException((char*)"DisplayWorlds was called before worlds were initialised");
        }
        glm::vec2 ss_pos = solarsystems[i]->getPosition();
        printf("\nSolar System %d - At position (%d, %d)\n", solarsystems[i]->getID(), static_cast<int>(ss_pos.x), static_cast<int>(ss_pos.y));
        for (int j=0; j < solarsystems[i]->getWorldCount(); j++) {
            if (stepcount >= steps && steps != 0) {
              stepcount = 0;
              std::cout << "Enter 'd' to display next worlds. 'q' to quit." << std::endl;
              std::cin >> input;
              if (input[0] == 'q') { return; }
            }
            if ((pop_flag && worlds[j]->getIsPopulated()) || !pop_flag) {
                DisplayWorld(worlds[j], &maxpop, &minpop);
                if (pos_flag) {
                    printf("World position: (%f, %f)\n", worlds[j]->getPosition().x, worlds[j]->getPosition().y);
                }
                stepcount++;
            }
            
        }
    }
    
    printf("\nLowest population: %lu\nHighest population: %lu\n\n", minpop, maxpop);
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
