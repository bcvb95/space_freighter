#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <display.h>
#include <camera.h>
#include <gameobject.h>

#define WIDTH 800
#define HEIGHT 500

int main(int argc, char** argv)
{
    Display* window = new Display(WIDTH, HEIGHT, argv[0]+2);

    Camera* cam = new Camera(glm::vec3(0,0,10), (float)WIDTH, (float)HEIGHT, 0);

    DrawableGameObject* go1 = new DrawableGameObject("GO 1", "../res/tex.png", "../res/basicShader");
    go1->GetTransform()->GetPos()->z -= 5;
    DrawableGameObject* go2 = new DrawableGameObject ("GO 2", "../res/img1.png", "../res/basicShader");

    std::cout << "Hello world!\n";

    SDL_Event e;
    bool isRunning = true;
    float counter = 0.0;

    while(isRunning) 
    {
        window->Clear(0.0f, 0.2f, 0.0f, 1.0f);

        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                isRunning = false;
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym) // camera controls
                {
                    case SDLK_w:
                        cam->GetPos()->y += 0.1;
                        break;
                    case SDLK_s:
                        cam->GetPos()->y -= 0.1;
                        break;
                    case SDLK_a:
                        cam->GetPos()->x -= 0.1;
                        break;
                    case SDLK_d:
                        cam->GetPos()->x += 0.1;
                        break;
                    case SDLK_z:
                        cam->Zoom(-0.05f);
                        break;    
                    case SDLK_x:
                        cam->Zoom(0.05f);
                        break;    
                }
            }
        }

        go1->GetTransform()->GetPos()->x = cos(counter)*2;
        
        go2->DrawSprite(cam);
        go1->DrawSprite(cam);

        counter += 0.01;

        window->SwapBuffers();
        SDL_Delay(1);
    } 

    std::cout << "Cleaning up" << std::endl;

    delete go1;
    delete go2;
    delete cam;
    delete window;

    return 0;
}