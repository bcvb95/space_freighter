#include <input_handler.h>

#define MOUSEPAN_SPEEDFAC 0.8f;


InputHandler::InputHandler(const Uint8* keystate, Camera* cam, Display* window, GUI::Canvas* canvas)
{
    m_keystate = keystate; 
    m_cam = cam; 
    m_window = window;
    m_canvas = canvas;
}

void InputHandler::HandleInput(SDL_Event* e, float delta_time, bool* isGameRunning, float* time_mul)
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

    /// HANDLE MOUSE CAMERA PAN 
    glm::vec3 cam_dir(0,0,0); // For camera movement 
    if( m_mousePosScreen.x >= winWidth-5 || m_mousePosScreen.x <= 5
        || m_mousePosScreen.y >= winHeight-5 || m_mousePosScreen.y <= 5) 
    {
        if (m_mousePosScreen.x >= m_window->GetWindowWidth()-5)
            cam_dir.x = 1.0 * MOUSEPAN_SPEEDFAC;
        if (m_mousePosScreen.x <= 5)
            cam_dir.x = -1.0 * MOUSEPAN_SPEEDFAC;
        if (m_mousePosScreen.y >= m_window->GetWindowHeight()-5)
            cam_dir.y = -1.0 * MOUSEPAN_SPEEDFAC;
        if (m_mousePosScreen.y <= 5)
            cam_dir.y = 1.0 * MOUSEPAN_SPEEDFAC;
        // move camera
        m_cam->Move(cam_dir, delta_time);
    }
    /// HANDLE EVENTS
    while(SDL_PollEvent(e))
    {
        SDL_PumpEvents(); // ensures keystate update

        // check for game exit
        if (e->type == SDL_QUIT || m_keystate[SDL_SCANCODE_ESCAPE])
            *isGameRunning = false;


        // Mouse click
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            if (e->button.button == SDL_BUTTON_LEFT) {
                m_canvas->MouseInBounds(m_mousePosScreen, true);
            } 
        }

        HandleCamInput(e, delta_time);

        // Handle input for setting time speed
        if (time_mul != NULL) {
            if (m_keystate[SDL_SCANCODE_1])
                *time_mul = 1.0f;
            else if (m_keystate[SDL_SCANCODE_2])
                *time_mul = 5.0f;
            else if (m_keystate[SDL_SCANCODE_3])
                *time_mul = 10.0f;
            else if (m_keystate[SDL_SCANCODE_4])
                *time_mul = 100.0f;
            else if (m_keystate[SDL_SCANCODE_5])
                *time_mul = 1000.0f;
        }

        // LSHIFT + P to print mouse world position
        if (m_keystate[SDL_SCANCODE_P] && m_keystate[SDL_SCANCODE_LSHIFT])
        {
            std::cout<<"Mouse position world (X,Y) = (" << m_mousePosWorld.x<<","<<m_mousePosWorld.y<<")"<< std::endl;
            std::cout<<"Mouse position screen (X,Y) = (" << m_mousePosScreen.x<<","<<m_mousePosScreen.y<<")"<< std::endl;

        }

        
    }
}

void InputHandler::HandleCamInput(SDL_Event* e , float delta_time)
// for handling camera input functionality 
{

    glm::vec3 cam_dir(0,0,0); // For camera movement 

    // CAMERA INPUT
    // Camera input with keys(WASDZX)/and mousewheel scroll-zoom
    if (e->type == SDL_KEYDOWN || e->type == SDL_MOUSEWHEEL)
    {   
        if (e->type == SDL_MOUSEWHEEL) { 
            if (e->wheel.y > 0) { // if scrolling up(zoom in)
                m_cam->Zoom(true, delta_time); 
            } else { // scrolling down(zoom out)
                m_cam->Zoom(false, delta_time);
            } 
        }
        if (e->type == SDL_KEYDOWN) // Keypress camera movement
        {
            // Camera zooom
            if (m_keystate[SDL_SCANCODE_Z]) 
                m_cam->Zoom(true, delta_time);
            if (m_keystate[SDL_SCANCODE_X]) 
                m_cam->Zoom(false, delta_time);

            // Camera pan movement
            if (m_keystate[SDL_SCANCODE_W])
                cam_dir.y += 1;
            if (m_keystate[SDL_SCANCODE_S])
                cam_dir.y += -1;
            if (m_keystate[SDL_SCANCODE_D])
                cam_dir.x += 1;
            if (m_keystate[SDL_SCANCODE_A])
                cam_dir.x += -1;
            m_cam->Move(cam_dir, delta_time);
            //// END CAMERA InPUT HANDLE ///
        }
    }
}