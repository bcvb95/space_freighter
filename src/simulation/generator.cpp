#include "generator.h"

namespace Simulation {
    Generator::Generator(std::mt19937* _mtgen) {
      this->m_mtgen = _mtgen;
      LoadWorldNames();
    }

    Generator::~Generator() {
      for (unsigned int i = 0; i < this->namecount; i++) {
        free(possible_world_names[i]);
      }
    }

  void Generator::GenerateUniverse (Universe* _universe) {
    this->universe = _universe;
    this->GenerateAllWorlds();
  }

  void Generator::GenerateAllWorlds () {
    std::uniform_real_distribution<float> diffspecies_dist(1, SPECIES_MAX+1);
    std::normal_distribution<float> population_dist(100, 40); 
    for (int i=0; i < this->universe->getSize(); i++) {
      World* newWorld = new World(i);
      float sample = population_dist(*this->m_mtgen);
      if (sample <= 0.0f) { sample = 0.0f; }
      
      unsigned long max_pop = static_cast<unsigned long>(sample);
      switch (rand() % 3) {
        case 0:
          max_pop *= HIGH_POPULATION;
          break;
        case 1:
          max_pop *= MED_POPULATION;
          break;
        default:
          max_pop *= LOW_POPULATION;
          break;
      }
      
      if (max_pop < 0) { max_pop = 0; }

      this->GenerateWorld(newWorld, diffspecies_dist(*this->m_mtgen), max_pop);
      this->universe->setIthWorld(i, newWorld);
    }
  }

  void Generator::GenerateWorld (World* world, int different_species, unsigned long max_world_pop) {
    // Name
    char* name = (char*)malloc(sizeof(char)*50);
    char* unique_name = this->GetUniqueWorldName();
    if (unique_name != NULL) {
      strcpy(name, unique_name);
    }
    // Species
    unsigned long pop_count[SPECIES_MAX] = {0};
    int is_populated = rand() % 10;
    if (is_populated == 0 && max_world_pop != 0) {
      int rand_ints[different_species];
      RandomUniqueIntegers(different_species, 0, SPECIES_MAX-1, rand_ints);
      unsigned long pop_left = max_world_pop;
      for (int i=0; i < different_species; i++) {
        if (i == different_species-1) {
          pop_count[rand_ints[i]] = pop_left;
        }
        else {
          pop_count[rand_ints[i]] = pop_left / (rand() % 3 + different_species + i*2);
          pop_left -= pop_count[rand_ints[i]];

          if (pop_left <= 0) {
            break;
          }
        }
      }
    }
    unsigned long tradehub_count;
    unsigned long spacestation_count;
    if (max_world_pop > 0 && is_populated == 0) {
      tradehub_count = POP_PER_TRADEHUB % max_world_pop + 1;
      tradehub_count += rand() % tradehub_count - tradehub_count / 2;

      spacestation_count = POP_PER_SPACESTATION % max_world_pop;
      if (spacestation_count > 0 ) {
        spacestation_count += rand() % spacestation_count - spacestation_count;
      }
    }
    else {
      tradehub_count = 0;
      spacestation_count = 0;
    }
    
    world->Init((unsigned char*) name, pop_count, static_cast<unsigned int>(tradehub_count), static_cast<unsigned int>(spacestation_count));
  }

  char* Generator::GetUniqueWorldName () {
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

  int Generator::CheckDuplicateNames (char* name) {
    int i;
    for (i=0; i < this->universe->getSize(); i++) {
      if (this->universe->getIthWorld(i) == NULL) { return 0; }

      if (strcmp(this->universe->getIthWorld(i)->getName(), name) == 0) {
        return 1;
      }
    }
    return 0;
  }

  void Generator::LoadWorldNames () {
    FILE* namefile;
    unsigned int _namecount = 0;
    char name[50] = {0};
    namefile = fopen("../res/planet_names.txt", "r");
    if (namefile == NULL) throw WorldNameFileException();
    else {
      while ( fgets(name, 50, namefile) != NULL ) {
        if (_namecount >= MAX_UNIQUE_NAMES) { _namecount--; break; }
        this->possible_world_names[_namecount] = (char*) malloc(sizeof(unsigned char)*50);
        memset(this->possible_world_names[_namecount], 0, 50);
        // Copy but exclude newline
        strncpy(this->possible_world_names[_namecount], name, strlen(name)-1);
        _namecount++;
      }
      this->namecount = _namecount;
      fclose(namefile);
    }
  }
}