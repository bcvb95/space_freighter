#include <input_handler.h>

InputHandler::InputHandler(const Uint8* keystate, Camera* cam)
{
    m_keystate = keystate; 
    m_cam = cam;
}

void InputHandler::HandleInput(SDL_Event* e, float delta_time, bool* isGameRunning)
{
    while(SDL_PollEvent(e))
    {
        if (e->type == SDL_QUIT)
            *isGameRunning = false;

        // CAMERA INPUTS
        else if (e->type == SDL_KEYDOWN || e->type == SDL_MOUSEBUTTONDOWN 
                || e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP 
                || e->type == SDL_MOUSEWHEEL)
        {   
            // get mousestate
            
            /// CAMERA INPUT ////
            glm::vec3 cam_dir(0,0,0); // default camera moving direction.
            SDL_PumpEvents();
            // Camera zooo
            if (m_keystate[SDL_SCANCODE_Z])
                *m_cam->GetZoom() -= 0.05;
            if (m_keystate[SDL_SCANCODE_X])
                *m_cam->GetZoom() += 0.05;

            // Camera pan movement
            if (m_keystate[SDL_SCANCODE_W])
                cam_dir.y += 1;
            if (m_keystate[SDL_SCANCODE_S])
                cam_dir.y += -1;
            if (m_keystate[SDL_SCANCODE_D])
                cam_dir.x += 1;
            if (m_keystate[SDL_SCANCODE_A])
                cam_dir.x += -1;


            // Mouse pan
            int x,y;
            SDL_GetMouseState(&x,&y);
            std::cout<<"x="<<x<<", y="<<y<<std::endl;

            // update camera
            m_cam->Update(cam_dir, delta_time);
            //// END CAMERA InPUT HANDLE ///
        }
    }
}