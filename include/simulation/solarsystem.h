#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "SimConstants.h"
#include "world.h"
#include <glm/glm.hpp>
#include "custom_exceptions.h"

namespace Simulation {
    class SolarSystem {
        public:
            SolarSystem(int ID);
            ~SolarSystem(void);

            void Init(glm::vec2);
            void Update(float dt);

            void AddWorld (World* newworld);
            int getID() { return this->ID; }
            glm::vec2 getPosition() { return this->position; }
            int getWorldCount() { return this->world_count; }
            World** getWorlds() { return this->worlds; }
        private:
            int ID;
            glm::vec2 position = glm::vec2(MAX_XY_WORLDPOS+1, MAX_XY_WORLDPOS+1);
            World* worlds[MAX_WORLDS_PER_SOLARSYSTEM] = {NULL};
            int world_count = 0;
            
    };
}

#endif