#include <core_utils.h>

glm::vec2 ScreenToWorld(glm::vec2 scr_coords, Camera* cam)
{
    double mx = (2.0f * scr_coords.x) / (cam->GetWindow()->GetWindowWidth())-1.0f;
    double my = (-2.0f * scr_coords.y) / (cam->GetWindow()->GetWindowHeight())+1.0f;
    glm::mat4 invProj = glm::inverse(cam->GetViewProjectionMatrix());
    glm::vec4 wCoord(mx, my, 0, 1);
    wCoord = invProj * wCoord;

    return glm::vec2(wCoord.x, wCoord.y);
}; 

glm::vec2 WorldToScreen(glm::vec3 world_coord, Camera* cam)
{
    glm::vec3 point3d = cam->GetViewProjectionMatrix() * glm::vec4(world_coord, 1);
    float scr_x = (int) std::roundf(((point3d.x+1)/2.0f)*cam->GetCamWidth());
    float scr_y = (int) std::roundf(((1-point3d.y)/2.0f)*cam->GetCamHeight());

    int x = (int)std::roundf(scr_x * (static_cast<float>(cam->GetWindow()->GetWindowWidth()) / cam->GetCamWidth()));
    int y = (int)std::roundf(scr_y * (static_cast<float>(cam->GetWindow()->GetWindowHeight()) / cam->GetCamHeight()));
     
    return glm::vec2(x, y);
}