#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>
#include <display.h>
#include <text_renderer.h>
#include <camera.h>
#include <gameobject.h>
#include <input_handler.h>
#include <gui_objects.h>

#define WIDTH 800
#define HEIGHT 500

glm::vec4 purple(1.0f,0.0f,1.0f,1.0f);
glm::vec4 black(0.0f,0.0f,0.0f,1.0f);

using namespace GUI;

void ClickFunction() { std::cout << "CLICKED!" << std::endl; }

int main(int argc, char** argv)
{
    // window/display, camera and clock-struct
    Display* window = new Display(WIDTH,HEIGHT, argv[0]+2);
    Camera* cam = new Camera(glm::vec3(0,0,0), 0, window);
    Clock clock;

    // basic shader
    BasicShader* shader1 = new BasicShader("../res/basicShader", cam);
    TextShader* text_shader = new TextShader("../res/textShader", cam);
    GUI_Shader* gui_shader = new GUI_Shader("../res/gui_shader", cam);
    TextRenderer* text_rend = new TextRenderer(text_shader, "../res/FreeSans.ttf");

    //
    Texture* texture1 = new Texture("../res/tex.png");
    Texture* texture2 = new Texture("../res/img1.png");
    Texture* texture3 = new Texture("../res/buttontex.png");
    
    // init gui  
    Canvas* canvas = new Canvas(window); 
    Panel* panel1 = canvas->NewPanel(glm::vec2(0.25f, 0.25f), glm::vec2(0.75f, 0.25f), glm::vec2(0.25f, 0.75f), glm::vec2(0.75f, 0.75f));
    Panel* panel2 = canvas->NewPanel(glm::vec2(0.25f, 0.25f), glm::vec2(0.75f, 0.25f), glm::vec2(0.25f, 0.75f), glm::vec2(0.75f, 0.75f), panel1);

    panel1->InitTexture(gui_shader, texture2);
    panel2->InitTexture(gui_shader, texture1);

    Label* label1 = canvas->NewLabel(glm::vec2(0.1f,0.8f), panel1, text_rend, "hello", FS_18);

    Button* button1 = canvas->NewButton(glm::vec2(0.1f), glm::vec2(0.4f, 0.1f), glm::vec2(0.1f, 0.3f), glm::vec2(0.4f, 0.3f), panel2);
    button1->InitTexture(gui_shader, texture3);
    button1->SetOnClick(ClickFunction);
    
    // initlialize textrenderer with font.

    // 
    DrawableGameObject* go1 = new DrawableGameObject("GO 1", texture2, shader1);  

    go1->GetTransform()->GetScale()->x *= 10;
    go1->GetTransform()->GetScale()->y *= 10;

    
    // Input handling
    SDL_Event e;
    const Uint8* keystate = SDL_GetKeyboardState(nullptr); // holds a snapshot of the keyboard.
    bool isRunning = true;

    InputHandler* input_handler = new InputHandler(keystate, cam, window, canvas);

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


        panel1->Draw(cam);
        
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
