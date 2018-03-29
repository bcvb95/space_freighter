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
    Camera* cam = new Camera(glm::vec3(0,0,2), 70.0f, (float)WIDTH/(float)HEIGHT, 0.001f, 1000.0f);

    DrawableGameObject* go1 = new DrawableGameObject("GO 1", "../res/tex.png", "../res/basicShader");
    DrawableGameObject* go2 = new DrawableGameObject ("GO 2", "../res/tex.png", "../res/basicShader");

    go2->GetTransform()->GetPos()->z = -10;

    go2->GetTransform()->GetScale()->y *= 1000;
    go2->GetTransform()->GetScale()->x *= 1000;

    std::cout << go2->GetTransform()->GetScale()->y << std::endl;
    
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
                switch(e.key.keysym.sym)
                {
                    case SDLK_w:
                        cam->GetPos()->y -= 50;
                        break;
                    case SDLK_s:
                        cam->GetPos()->y += 50;
                        break;
                    case SDLK_a:
                        cam->GetPos()->x -= 50;
                        break;
                    case SDLK_d:
                        cam->GetPos()->x += 50;
                        break;
                    case SDLK_z:
                        go2->GetTransform()->GetScale()->x *= 0.80f;
                        go2->GetTransform()->GetScale()->y *= 0.80f;
                        break;    
                    case SDLK_x:
                        go2->GetTransform()->GetScale()->x *= 1.20f;
                        go2->GetTransform()->GetScale()->y *= 1.20f;
                        break;    
                }
            }
        }

        go2->GetTransform()->GetRot()->y = sin(counter);
        go2->DrawSprite(cam);


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