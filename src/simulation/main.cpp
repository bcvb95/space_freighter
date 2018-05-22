#include <iostream>
#include "mainsim.h"
#include "custom_sim_exceptions.h"
#include <unistd.h>

void ExtractNumber(char*, int*);

int main (int argc, char *argv[]) {
  std::cout << "Starting up simulation" << std::endl;

  unsigned int simulation_seed = 123454321;
  int universe_size = 949;
  int delta_time = 5;

  Simulation::MainSim* sim;
  try {
    sim = new Simulation::MainSim();
    sim->Init(simulation_seed, universe_size);
  } 
  catch ( const Simulation::GeneratorException &e ) {
    std::cout << "Error in Generator while starting up: " << e.what() << std::endl;
    return 1;
  }
  catch ( const Simulation::UniverseException &e ) {
    std::cout << "Error in Universe while starting up: " << e.what() << std::endl;
    return 1;
  }
  catch ( const Simulation::SimulationException &e) {
    std::cout << "Error in main simulation while starting up: " << e.what() << std::endl;
  }
  
  static int inputsize = 100;
  char input[inputsize];
  bool isRunning = true;
  int number, displaysteps;
  bool readflags, pop_flag, pos_flag;
  std::cout << "Running simulation" << std::endl;
  while (isRunning) {
    for (int i=0; i < inputsize; i++) { input[i] = 0; }
    std::cout << "Enter: 'c' to update simulation. 'd' to display worlds. 'h' for help (extra flags etc.). 'q' to quit." << std::endl;
    std::cin >> input;
    switch (input[0]) {
      case 'q':
        isRunning = false;
        break;
      case 'h':
        std::cout << "--- HELP ---" << std::endl;
        std::cout << "Updating Simulator with 'c':" << std::endl;
        break;
      case 'c':
        ExtractNumber(input, &number);
        if (number != '\0') {
          std::cout << "Updating " << number << " times." << std::endl;
          for (int i = 0; i < number; i++) {
            sim->Update(1);
          }
        }
        else {
          std::cout << "Updating once." << std::endl;
          sim->Update(1);
        }
        break;
      case 'l':
        while (1) {
          sim->Update(1);
          sleep(1);
        }
      case 'd':
        readflags = pop_flag = pos_flag = false;
        displaysteps = 0;
        ExtractNumber(input, &displaysteps);
        for (int i=1; i<inputsize; i++) {
          if (input[i] == '\0') { break; }
          if (readflags) {
            if (input[i] == 'p') { pop_flag = true; }
            else if (input[i] == 'w') { pos_flag = true; }
            else if (input[i] == ' ') { break; }
            else { std::cout << "Unknow flag -" << input[i] << std::endl; }
          }
          else if (input[i] == '-') { readflags = true; }
        }
        sim->DisplayWorlds(pop_flag, displaysteps, pos_flag);
        break;
      default:
        std::cout << "Command not understood" << std::endl;
    }
  }
  std::cout << "Ending simulation" << std::endl;
  delete sim;
  return 0;
}

void ExtractNumber (char* str, int* res) {
  int number = 0;
  int numcount = 0;
  int multiplier = 1;
  char ch;

  while ( str[numcount+1] != 0 ) {
    ch = str[numcount+1];
    if ((int)ch >= 48 && (int)ch <= 57) { numcount++; multiplier *= 10; }
    else { break; }
  }
  for (int i=0; i < numcount; i++) {
    multiplier /= 10;
    number += ((int)str[i+1] - '0') * multiplier;
  }
  *res = number;
}