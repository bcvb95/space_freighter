#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <camera.h>

class InputHandler
{
public:
    InputHandler(const Uint8* keystate, Camera* cam);
    
    void HandleInput(SDL_Event* e, float delta_time, bool* isGameRunning);


protected:
private:
    const Uint8* m_keystate;
    Camera* m_cam;
    glm::vec2 m_mousePos;

};

#endif