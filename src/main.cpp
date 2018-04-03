#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <display.h>
#include <camera.h>
#include <gameobject.h>
#include <input_handler.h>

#include <ft2build.h>
#include FT_FREETYPE_H


#define WIDTH 800
#define HEIGHT 500

int main(int argc, char** argv)
{
    Display* window = new Display(WIDTH, HEIGHT, argv[0]+2);
    Camera* cam = new Camera(glm::vec3(0,0,0), (float)WIDTH, (float)HEIGHT, 0, window);
    Clock clock;

    Shader* shader1 = new Shader("../res/basicShader");
    Texture* texture1 = new Texture("../res/tex.png");
    Texture* texture2 = new Texture("../res/img1.png");

    DrawableGameObject* go1 = new DrawableGameObject("GO 1", texture1, shader1);  
    DrawableGameObject* go2 = new DrawableGameObject("GO 2", texture2, shader1);  

    go1->GetTransform()->GetScale()->x *= 10;
    go1->GetTransform()->GetScale()->y *= 10;

    std::cout << "Hello world!\n";

    SDL_Event e;
    const Uint8* keystate = SDL_GetKeyboardState(nullptr); // holds a snapshot of the keyboard.
    bool isRunning = true;

    InputHandler* input_handler = new InputHandler(keystate, cam, window);

    float delta_time;    
    float counter = 0.0;

    while(isRunning) 
    {
        window->Clear(0.0f, 0.2f, 0.0f, 1.0f);

        clock.tick();
        delta_time = clock.delta_time / 1000.0; // in seconds.
        
        //// HANDLE INPUT HERE
        input_handler->HandleInput(&e, delta_time, &isRunning);
        /// END INPUT HANDLING

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

    // delete texs and shaders
    delete shader1;
    delete texture1;
    delete texture2;

    return 0;
}
