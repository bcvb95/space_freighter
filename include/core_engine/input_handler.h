#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <display.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <camera.h>
#include <core_utils.h>
#include <gui_objects.h>

enum ScrollValue {
    SCROLL_IN,
    SCROLL_OUT,
    SCROLL_NONE
};

struct ClickStruct {
    bool m_left_held = false;
    bool m_right_held = false;
};

class InputHandler
{
public:
    InputHandler(Camera* cam, Display* window, GUI::Canvas* canvas);
    ~InputHandler();
    
    void HandleInput(SDL_Event* e, float delta_time, bool* isGameRunning, int* time_mul = NULL);

protected:
private:
    int m_numkeys;
    const Uint8* m_keystate;
    bool* m_keyheld;
    ClickStruct m_mouseclicks;
    ScrollValue m_scrollvalue = SCROLL_NONE;
    Camera* m_cam;
    Display* m_window;
    GUI::Canvas* m_canvas;

    glm::vec2 m_mousePosScreen;
    glm::vec2 m_mousePosWorld;
};
#endif