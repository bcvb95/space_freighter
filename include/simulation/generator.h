#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <random>
#include <stdlib.h>
#include <string.h>
#include "universe.h"
#include "world.h"
#include "SimConstants.h"
#include "simutils.h"
#include "custom_exceptions.h"


namespace Simulation {
    class Generator {
        public:
            Generator(std::mt19937* _mtgen);
            ~Generator(void);
            
            void GenerateUniverse(Universe*);
        private:
            void GenerateAllWorlds();
            void GenerateWorld(World*, int, unsigned long);
            glm::vec2 GetNewSolarSystemPosition();
            char* GetUniqueWorldName();
            int CheckDuplicateNames(char*);
            void LoadWorldNames();

            Universe* universe;
            std::mt19937* m_mtgen;

            char* possible_world_names[MAX_UNIQUE_NAMES] = {0};
            unsigned int namecount;
    };
}

#endif