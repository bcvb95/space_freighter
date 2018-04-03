#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <camera.h>

glm::vec2 ScreenToWorld(glm::vec2 scr_coords, float winWidth, float winHeight, Camera* cam);

#endif