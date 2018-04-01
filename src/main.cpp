#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <display.h>
#include <camera.h>
#include <gameobject.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 500

int main(int argc, char** argv)
{
    Display* window = new Display(WIDTH, HEIGHT, argv[0]+2);
    Camera* cam = new Camera(glm::vec3(0,0,1), (float)WIDTH, (float)HEIGHT, 0);
    Clock clock;


    Shader* shader1 = new Shader("../res/basicShader");
    Texture* texture1 = new Texture("../res/tex.png");
    Texture* texture2 = new Texture("../res/img1.png");

    DrawableGameObject* go1 = new DrawableGameObject("GO 1", texture1, shader1);  
    DrawableGameObject* go2 = new DrawableGameObject("GO 2", texture2, shader1);  
    go1->GetTransform()->GetScale()->x *= 10;
    go1->GetTransform()->GetScale()->y *= 10;
    go2->GetTransform()->GetPos()->y = 0;

    std::cout << "Hello world!\n";

    SDL_Event e;
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    
    bool isRunning = true;

    float delta_time;    

    float counter = 0.0;

    while(isRunning) 
    {
        clock.tick();
        delta_time = clock.delta_time / 1000.0; // in seconds.

        window->Clear(0.0f, 0.2f, 0.0f, 1.0f);

        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                isRunning = false;
            else if (e.type == SDL_KEYDOWN)
            {
                glm::vec3 cam_dir(0,0,0);
                SDL_PumpEvents();
                // panning cammera
                if (keystate[SDL_SCANCODE_W])
                    cam_dir.y += 1;
                if (keystate[SDL_SCANCODE_S])
                    cam_dir.y += -1;
                if (keystate[SDL_SCANCODE_D])
                    cam_dir.x += 1;
                if (keystate[SDL_SCANCODE_A])
                    cam_dir.x += -1;
                if (keystate[SDL_SCANCODE_Z])
                    *cam->GetZoom() -= 0.05;
                if (keystate[SDL_SCANCODE_X])
                    *cam->GetZoom() += 0.05;
                // zooming camera
                cam->Update(cam_dir, delta_time);
            }
        }
        //std::cout<< "Cam zoom: " << *cam->GetZoom() << std::endl;
<<<<<<< HEAD
=======
        cam->UpdateWithZoom();
        go1->GetTransform()->GetRot()->x = cos(counter)*2;
>>>>>>> b5ef1ec1310d6aefb8825def340673b2fc8e831d
        
        go1->DrawSprite(cam);
        go2->DrawSprite(cam);

        counter += 0.01;

        window->SwapBuffers();
        //SDL_Delay(1);
    } 

    std::cout << "Cleaning up" << std::endl;

    delete go1;
    delete go2;
    delete cam;
    delete window;

    // delete texs and shaders
    delete shader1;
    delete texture1;
    delete texture2;

    return 0;
}
