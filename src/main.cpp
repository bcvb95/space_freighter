#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>
#include <display.h>
#include <text_renderer.h>
#include <camera.h>
#include <gameobject.h>
#include <input_handler.h>

#define WIDTH 800
#define HEIGHT 500

int main(int argc, char** argv)
{
    // window/display, camera and clock-struct
    Display* window = new Display(WIDTH, HEIGHT, argv[0]+2);
    Camera* cam = new Camera(glm::vec3(0,0,0), (float)WIDTH, (float)HEIGHT, 0, window);
    Clock clock;

    // basic shader
    BasicShader* shader1 = new BasicShader("../res/basicShader", cam);
    TextShader* text_shader = new TextShader("../res/textShader", cam);

    // initlialize textrenderer with font.
    TextRenderer* text_rend = new TextRenderer(text_shader);
    text_rend->LoadFont("../res/FreeSans.ttf", 48);
    glm::vec4 purple(1.0f,0.0f,1.0f,1.0f);
    glm::vec4 black(0.0f,0.0f,0.0f,1.0f);

    Texture* texture1 = new Texture("../res/tex.png");
    Texture* texture2 = new Texture("../res/img1.png");

    DrawableGameObject* go1 = new DrawableGameObject("GO 1", texture2, shader1);  

    go1->GetTransform()->GetScale()->x *= 10;
    go1->GetTransform()->GetScale()->y *= 10;
    //go1->GetTransform()->GetRot()->y += 3.14f;


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

        go1->DrawSprite();

        text_rend->RenderText("This is text!", 20.0f, 20.0f, 1.0f, purple);

        counter += 0.01;

        window->SwapBuffers();
        SDL_Delay(1);
    } 

    std::cout << "Cleaning up" << std::endl;

    delete go1;
    delete cam;
    delete window;

    // delete texs and shaders
    delete shader1;
    delete texture1;
    delete texture2;

    return 0;
}
