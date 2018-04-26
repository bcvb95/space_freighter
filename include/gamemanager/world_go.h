#ifndef WORLD_GO_H
#define WORLD_GO_H

#include "world.h"
#include "gameobject.h"

class WorldGO : public DrawableGameObject {
    public:
        WorldGO(const std::string& go_name, Texture* _texture, BasicShader* _shader, Simulation::World* _world);
        ~WorldGO();

        void DrawSprite();
    private:
        Simulation::World* m_world;
};

#endif