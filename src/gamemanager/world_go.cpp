#include "world_go.h"

WorldGO::WorldGO(const std::string& go_name, Texture* _texture, Shader* _shader, Simulation::World* _world) 
:  DrawableGameObject(go_name, _texture, _shader) 
{
    this->m_world = _world;
}

WorldGO::~WorldGO() {

}

void WorldGO::DrawSprite(Camera* cam) {
    glm::vec2 world_pos = this->m_world->getPosition();
    this->m_transform->SetPos(glm::vec3(world_pos.x, world_pos.y, 0));
    DrawableGameObject::DrawSprite(cam);
}