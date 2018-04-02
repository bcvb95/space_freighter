#ifndef WORLD_H
#define WORLD_H

#include <stdlib.h>
#include <cmath>
#include <glm/glm.hpp>
#include "simutils.h"
#include "SimConstants.h"

namespace Simulation {
    class World {
        public:
            World(int, int);
            ~World(void);

            void Init(const unsigned char*, unsigned long[], unsigned int, unsigned int);
            void Update(float dt);

            void SetOrbit(int orbit_layer, float speed, int start_degree, glm::vec2* solarsys_pos);
            int getID() { return this->ID; }
            char* getName() { return (char*)this->name; }
            glm::vec2 getPosition() { return this->position; }
            unsigned long* getPopulation() { return this->popu_count; }
            unsigned int getTradehubCount() { return this->tradehub_count; }
            unsigned int getSpacestationCount() { return this->spacestation_count; }
            bool getIsPopulated() { return this->is_populated; }
            void setIsPopulated(bool b) { this->is_populated = b; }
        private:
            int ID;
            int solar_system_ID;
            const unsigned char* name = 0;
            bool is_populated = false;
            unsigned long popu_count[SPECIES_MAX] = {0};
            unsigned int tradehub_count;
            unsigned int spacestation_count;

            // orbit in system
            void UpdateOrbit(float step);
            glm::vec2 position;
            glm::vec2* system_position;
            glm::vec2 orbit_radius;
            
            float orbital_speed;
            float orbital_degree;
    };

}

#endif
