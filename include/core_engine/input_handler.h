#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <display.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <camera.h>
#include <core_utils.h>
#include <gui_objects.h>

class InputHandler
{
public:
    InputHandler(const Uint8* keystate, Camera* cam, Display* window, GUI::Canvas* canvas);
    
    void HandleInput(SDL_Event* e, float delta_time, bool* isGameRunning, float* time_mul = NULL);
    void HandleCamInput(SDL_Event* e, float delta_time);

protected:
private:
    const Uint8* m_keystate;
    Camera* m_cam;
    Display* m_window;
    GUI::Canvas* m_canvas;

    glm::vec2 m_mousePosScreen;
    glm::vec2 m_mousePosWorld;
};

#endif