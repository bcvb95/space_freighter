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
    Display window(WIDTH, HEIGHT, "Window 1");
    Camera cam(glm::vec3(0,0,5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.001f, 1000.0f);

    DrawableGameObject go1("GO 1", "../res/tex.png", "../res/basicShader");
    DrawableGameObject go2("GO 2", "../res/img1.png", "../res/basicShader");

    go2.GetTransform()->GetPos()->z = -10;
    go2.GetTransform()->GetPos()->x = -2;

    std::cout << "Hello world!\n";

    SDL_Event e;
    bool isRunning = true;
    float counter = 0.0;

    while(isRunning) 
    {
        window.Clear(0.0f, 0.2f, 0.0f, 1.0f);

        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                isRunning = false;
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_w:
                        cam.GetPos()->z -= 0.5;
                        break;
                    case SDLK_s:
                        cam.GetPos()->z += 0.5;
                        break;
                    case SDLK_a:
                        cam.GetPos()->x -= 0.5;
                        break;
                    case SDLK_d:
                        cam.GetPos()->x += 0.5;
                        break;

                }
            }
        }

        go1.GetTransform()->GetPos()->x = sin(counter);
        go1.DrawSprite(&cam);

        go2.GetTransform()->GetRot()->y = cos(counter)*2;
        go2.GetTransform()->GetRot()->x = cos(counter)*2;
        go2.DrawSprite(&cam);

        counter += 0.01;

        window.SwapBuffers();
        SDL_Delay(1);
    } 
    return 0;
}