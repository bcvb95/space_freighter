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
    SolarSystem* current_solar_system = 0;
    int current_ss_id;
    int worlds_to_next_system = 0;

    std::uniform_real_distribution<float> position_dist(MIN_XY_WORLDPOS, MAX_XY_WORLDPOS+1);
    std::uniform_real_distribution<float> diffspecies_dist(1, SPECIES_MAX+1);
    std::normal_distribution<float> population_dist(100, 40); 
    for (int i=0; i < this->universe->getWorldCount(); i++) {
      if (worlds_to_next_system <= 0) {
        if (current_solar_system != 0) { // Init solar system AFTER adding worlds
          current_solar_system->Init(glm::vec2(position_dist(*this->m_mtgen), position_dist(*this->m_mtgen)));
        }
        current_solar_system = new SolarSystem(this->universe->getSolarSystemCount());
        current_ss_id = current_solar_system->getID();
        this->universe->AddSolarSystem(current_solar_system);
        worlds_to_next_system = rand() % (MAX_WORLDS_PER_SOLARSYSTEM - MIN_WORLDS_PER_SOLARSYSTEM) + MIN_WORLDS_PER_SOLARSYSTEM;
      }
      World* newWorld = new World(i, current_ss_id);
      worlds_to_next_system--;

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
      current_solar_system->AddWorld(newWorld);
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
      world->setIsPopulated(true);
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
      tradehub_count = max_world_pop / POP_PER_TRADEHUB + 1;
      tradehub_count += rand() % tradehub_count - tradehub_count / 4;

      spacestation_count = max_world_pop / POP_PER_SPACESTATION;
      if (spacestation_count > 0 ) {
        spacestation_count += rand() % spacestation_count - spacestation_count / 2;
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
    for (i=0; i < this->universe->getWorldCount(); i++) {
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