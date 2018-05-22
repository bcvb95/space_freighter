#include <input_handler.h>

#define MOUSEPAN_SPEEDFAC 0.8f;


InputHandler::InputHandler(Camera* cam, Display* window, GUI::Canvas* canvas)
{
    m_keystate = SDL_GetKeyboardState(&m_numkeys); // holds a snapshot of the keyboard.
    m_keyheld = (bool*) malloc(sizeof(bool) * m_numkeys); // mask for held keys
    for (int i=0; i < m_numkeys; i++) { m_keyheld[i] = false; } // initialize keys to not be held
    m_cam = cam; 
    m_window = window;
    m_canvas = canvas;
}

InputHandler::~InputHandler() {
    free(m_keyheld);
}

void InputHandler::HandleInput(SDL_Event* e, float delta_time, bool* isGameRunning, int* time_mul)
{
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x,&y);
    m_mousePosScreen.x = static_cast<float>(x); 
    m_mousePosScreen.y = static_cast<float>(y); 

    // Get mouse position in world coordinates
    m_mousePosWorld = ScreenToWorld(m_mousePosScreen, m_cam);

    // update camera with mouse world coordinates
    m_cam->SetMouseWorldPos(m_mousePosWorld);
  
    float winWidth, winHeight; 
    winWidth = (float)m_window->GetWindowWidth();
    winHeight = (float)m_window->GetWindowHeight();

    m_scrollvalue = SCROLL_NONE;
    /// HANDLE EVENTS
    while(SDL_PollEvent(e))
    {
        SDL_PumpEvents(); // ensures keystate update

        // Game exit
        if (e->type == SDL_QUIT || m_keystate[SDL_SCANCODE_ESCAPE])
            *isGameRunning = false;

        // Mouse clicks
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            switch (e->button.button) {
                case SDL_BUTTON_LEFT:
                    m_mouseclicks.m_left_held = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    m_mouseclicks.m_right_held = true;
                    break;
            }
        }
        if (e->type == SDL_MOUSEBUTTONUP) {
            switch (e->button.button) {
                case SDL_BUTTON_LEFT:
                    m_mouseclicks.m_left_held = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    m_mouseclicks.m_right_held = false;
                    break;
            }
        }

        // Mouse wheel 
        if (e->type == SDL_MOUSEWHEEL) { 
            if (e->wheel.y > 0) {
                m_scrollvalue = SCROLL_IN;
            } else { 
                m_scrollvalue = SCROLL_OUT;
            } 
        }

        // Keypresses
        SDL_Keycode keyPressed = e->key.keysym.sym;
        if (keyPressed < m_numkeys) {
            if (e->type == SDL_KEYDOWN) // Keypress camera movement
            {
                m_keyheld[keyPressed] = true;
            }
            if (e->type == SDL_KEYUP) 
            {
                m_keyheld[keyPressed] = false;
            }
        }

        // LSHIFT + P to print mouse world position
        if (m_keystate[SDL_SCANCODE_P] && m_keystate[SDL_SCANCODE_LSHIFT])
        {
            std::cout<<"Mouse position world (X,Y) = (" << m_mousePosWorld.x<<","<<m_mousePosWorld.y<<")"<< std::endl;
            std::cout<<"Mouse position screen (X,Y) = (" << m_mousePosScreen.x<<","<<m_mousePosScreen.y<<")"<< std::endl;
        }
    }
  
    // Camera zooom
    if (m_keyheld[SDLK_z] || m_scrollvalue == SCROLL_IN) 
        m_cam->Zoom(true, delta_time);
    if (m_keyheld[SDLK_x] || m_scrollvalue == SCROLL_OUT) 
        m_cam->Zoom(false, delta_time);

    // Camera pan
    glm::vec3 cam_dir(0,0,0); 
    if (m_mousePosScreen.x >= m_window->GetWindowWidth()-5 || m_keyheld[SDLK_d])
        cam_dir.x = 1.0 * MOUSEPAN_SPEEDFAC;
    if (m_mousePosScreen.x <= 5 || m_keyheld[SDLK_a])
        cam_dir.x = -1.0 * MOUSEPAN_SPEEDFAC;
    if (m_mousePosScreen.y <= 5 || m_keyheld[SDLK_w])
        cam_dir.y = 1.0 * MOUSEPAN_SPEEDFAC;
    if (m_mousePosScreen.y >= m_window->GetWindowHeight()-5 || m_keyheld[SDLK_s])
        cam_dir.y = -1.0 * MOUSEPAN_SPEEDFAC;

    m_cam->Move(cam_dir, delta_time);

    // Mouse movement and clicks
    if (m_mouseclicks.m_left_held) {
        m_canvas->MouseInBounds(m_mousePosScreen, true);
    }

    // Handle input for setting time speed
    if (time_mul != NULL) {
        if (m_keyheld[SDLK_1])
            *time_mul = 1.0f;
        else if (m_keyheld[SDLK_2])
            *time_mul = 5.0f;
        else if (m_keyheld[SDLK_3])
            *time_mul = 10.0f;
        else if (m_keyheld[SDLK_4])
            *time_mul = 100.0f;
        else if (m_keyheld[SDLK_5])
            *time_mul = 1000.0f;
    }
}