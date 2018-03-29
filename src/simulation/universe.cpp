#include "universe.h"

namespace Simulation {

  Universe::Universe() {
    std::cout << "Constructing Universe." << std::endl;
    if (MAX_WORLDS > MAX_UNIQUE_NAMES) {
      throw IllegalMaxWorldsException();
    }
    LoadWorldNames();
  }


  Universe::~Universe() {
    std::cout << "Destructing Universe." << std::endl;
    for (unsigned int i = 0; i < this->namecount; i++) {
      free(possible_world_names[i]);
    }
    for (int i = 0; i < size; i++) {
      delete this->worlds[i];
    }
  }

  void Universe::Init(int size, std::mt19937* _mtgen) {
    if (size > MAX_WORLDS) {
      throw IllegalUniverseSizeException();
      return;
    }
    this->size = size;
    this->m_mtgen = _mtgen;
    this->GenerateAllWorlds();
  }

  void Universe::GenerateAllWorlds () {
    std::cout << "Generating worlds." << std::endl;
    std::uniform_real_distribution<float> diffspecies_dist(1, SPECIES_MAX+1);
    std::normal_distribution<float> population_dist(100, 40); 
    for (int i=0; i < this->size; i++) {
      World* newWorld = new World(i);
      float sample = population_dist(*this->m_mtgen);
      if (sample <= 0.0f) { sample = 0.0f; }
      std::cout << sample << std::endl;
      switch (rand() % 3) {
        case 0:
          sample *= HIGH_POPULATION;
        case 1:
          sample *= MED_POPULATION;
        default:
          sample *= LOW_POPULATION;
      }
      unsigned long long max_pop = static_cast<unsigned long long>(sample);
      if (max_pop < 0) { max_pop = 0; }
      GenerateWorld(newWorld, diffspecies_dist(*this->m_mtgen), max_pop);
      
      this->worlds[i] = newWorld;
    }
  }

  void Universe::GenerateWorld (World* world, int different_species, unsigned long long max_world_pop) {
    // Name
    char* name = (char*)malloc(sizeof(char)*50);
    char* unique_name = this->GetUniqueWorldName();
    strcpy(name, unique_name);
    // Species
    unsigned long long pop_count[SPECIES_MAX] = {0};
    int is_populated = rand() % 10;
    if (is_populated == 0 && max_world_pop != 0) {
      int rand_ints[different_species];
      RandomUniqueIntegers(different_species, 0, SPECIES_MAX-1, rand_ints);
      unsigned long long pop_left = max_world_pop;
      for (int i=0; i < different_species; i++) {
        if (i == different_species-1) {
          pop_count[rand_ints[i]] = pop_left;
        }
        else {
          pop_count[rand_ints[i]] = pop_left/2;///different_species;//rand() % pop_left;
          pop_left -= pop_count[rand_ints[i]];
          if (pop_left <= 0) {
            break;
          }
        }
      }
    }
    world->Init((unsigned char*) name, pop_count, 20, 5);
  }

  int Universe::CheckDuplicateNames (char* name) {
    int i;
    for (i=0; i < this->size; i++) {
      if (this->worlds[i] == NULL) { return 0; }

      if (strcmp(this->worlds[i]->getName(), name) == 0) {
        return 1;
      }
    }
    return 0;
  }

  char* Universe::GetUniqueWorldName () {
    int randidx;
    int count = 0;
    bool done = false;
    while (!done && count <= 5) {
      randidx = rand() % namecount;
      if (this->CheckDuplicateNames(this->possible_world_names[randidx]) == 0) {
        break;
      }
      count++;
    }
    if (count >= 5) {
      for (unsigned int i=0; i < this->namecount; i++) {
        if (this->CheckDuplicateNames(this->possible_world_names[i]) == 0) {
          return this->possible_world_names[i];
        }
      }
      throw NoMoreUniqueNamesException();
    }
    return this->possible_world_names[randidx];
  }

  void Universe::LoadWorldNames () {
    FILE* namefile;
    unsigned int namecount = 0;
    char name[50];
    namefile = fopen("../res/planet_names.txt", "r");
    if (namefile == NULL) throw WorldNameFileException();
    else {
      while ( fgets(name, 50, namefile) != NULL ) {
        this->possible_world_names[namecount] = (char*) malloc(sizeof(unsigned char)*50);
        strncpy(this->possible_world_names[namecount], name, strlen(name)-1); // Exclude newline
        namecount++;
      }
      this->possible_world_names[namecount] = NULL;
      this->namecount = namecount;
      fclose(namefile);
    }
  }
}
