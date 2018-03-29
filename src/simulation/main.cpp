#include <iostream>
#include "mainsim.h"
#include "custom_exceptions.h"

int main (int argc, char *argv[]) {
  std::cout << "Starting simulation" << std::endl;
  unsigned int simulation_seed = 123454321;
  Simulation::MainSim* sim;
  try {
    sim = new Simulation::MainSim();
    sim->Init(simulation_seed);
  } 
  catch ( const Simulation::UniverseException &e ) {
    std::cout << "Error in Universe: " << e.what() << std::endl;
    return 1;
  }
  catch ( const Simulation::SimulationException &e) {
    std::cout << "Error in main simulation: " << e.what() << std::endl;
  }
  sim->DisplayWorlds();
  delete sim;
  return 0;
}
