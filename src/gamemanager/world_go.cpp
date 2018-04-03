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
    // Idea: reposition draw of worlds depending on zoom factor of camera -
    // - the further out the zoom is, move the worlds towards the center of -
    // - the system so that they will be hidden behind it
    glm::vec2 system_pos = *this->m_world->getSolarSystemPosition();
    this->m_transform->SetPos(glm::vec3(world_pos.x, world_pos.y, 0));
    DrawableGameObject::DrawSprite(cam);
}