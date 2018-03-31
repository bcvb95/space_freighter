#include "universe.h"

namespace Simulation {

  Universe::Universe(int size) {
     if (size > MAX_WORLDS) {
      throw IllegalUniverseSizeException();
      return;
    }
    this->size = size;
    if (MAX_WORLDS > MAX_UNIQUE_NAMES) {
      throw IllegalMaxWorldsException();
    }
  }


  Universe::~Universe() {
    for (int i = 0; i < size; i++) {
      delete this->worlds[i];
    }
  }

  void Universe::Init() {
   
  }

  void Universe::Update(int stepsize) {
    for (int i=0; i < this->size; i++) {
      worlds[i]->Update(stepsize);
    }
  }

}
