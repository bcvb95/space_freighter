#include "world.h"
#include<iostream>
#include <stdio.h>
namespace Simulation {
    
    World::World (int _ID, int _ss_ID) {
        this->ID = _ID;
        this->solar_system_ID = _ss_ID;
        this->system_position = NULL;
    }

    World::~World() {
        free((void*)this->name);
    }

    void World::Init(const unsigned char* _name, unsigned long _popu_count[],
                    unsigned int _tradehub_count, unsigned int _spacestation_count) 
    {
        this->name = _name;
        for (int i=0; i < SPECIES_MAX; i++) {
          this->popu_count[i] = _popu_count[i];
        }
        this->tradehub_count = _tradehub_count;
        this->spacestation_count = _spacestation_count;
    }

    void World::Update(float dt) {
        if (this->system_position == NULL) {
            throw WorldWithoutSystemException();
        }
        this->UpdateOrbit(dt);
    }

    void World::UpdateOrbit(float dt) {
        this->orbital_degree += (dt * this->orbital_speed);
        if (this->orbital_degree >= 360.0f) { this->orbital_degree = 0.0f; }
        this->position.x = this->system_position->x + this->orbit_radius.x  * cos(this->orbital_degree);
        this->position.y = this->system_position->y + this->orbit_radius.y * sin(this->orbital_degree);
    }

    void World::SetOrbit(int _orbit_layer, float _speed, int _start_degree, glm::vec2* _solarsys_pos) {
        this->orbit_radius = glm::vec2( (ORBIT_BASESIZE + ORBIT_INC_X * pow(_orbit_layer, 1.1)) / 2.0f,
                                        (ORBIT_BASESIZE + ORBIT_INC_Y * pow(_orbit_layer, 1.1)) / 2.0f );
        this->system_position = _solarsys_pos;
        this->orbital_speed = _speed / pow(_orbit_layer, 2);
        if ( _start_degree > 360 ) { _start_degree = _start_degree % 360; }
        this->orbital_degree = _start_degree;
        this->UpdateOrbit(0);
    }
}
