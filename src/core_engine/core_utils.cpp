#include <core_utils.h>

glm::vec2 ScreenToWorld(glm::vec2 scr_coords, float winWidth, float winHeight, Camera* cam)
{
    double mx = (2.0f * scr_coords.x) / (winWidth)-1.0f;
    double my = (-2.0f * scr_coords.y) / (winHeight)+1.0f;
    glm::mat4 invProj = glm::inverse(cam->GetViewProjectionMatrix());
    glm::vec4 wCoord(mx, my, 0, 1);
    wCoord = invProj * wCoord;

    return glm::vec2(wCoord.x, wCoord.y);
}; 