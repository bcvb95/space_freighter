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

//void DisableClickFunction(void* button) { 
//    static_cast<Button*>(button)->Disable();
//}
//
//struct TwoButtons {
//    Button* button1;
//    Button* button2;
//    TwoButtons(Button* b1, Button* b2) : button1(b1), button2(b2) {}
//};
//
//void SwitchButtons(void* twobuttons) {
//    TwoButtons* tb_struct = static_cast<TwoButtons*>(twobuttons);
//    if (tb_struct->button1->IsDisabled()) {
//        tb_struct->button1->Enable();
//        tb_struct->button2->Disable();
//    } else {
//        tb_struct->button1->Disable();
//        tb_struct->button2->Enable();
//    }
//}

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
    Texture* texture1 = new Texture("../res/tex.png", false);
    Texture* texture2 = new Texture("../res/img1.png", false);
    Texture* texture3 = new Texture("../res/buttontex.png", true);

    Texture* texture_gui = new Texture("../res/tex.png", true);
    
    // init gui  
    Canvas* canvas = new Canvas(window); 
    Panel* panel1 = canvas->NewPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f));
    Panel* panel2 = canvas->NewPanel(glm::vec2(0.25f, 0.25f), glm::vec2(0.75f, 0.25f), glm::vec2(0.25f, 0.75f), glm::vec2(0.75f, 0.75f), panel1);

    panel1->InitTexture(gui_shader, texture_gui);
    panel2->InitTexture(gui_shader, texture1);
    panel2->Disable();

    Label* label1 = canvas->NewLabel(glm::vec2(0.0f,0.005f), panel1, text_rend, "FPS: ", FS_18);

    // Buttons
    Button* button1 = canvas->NewButton(glm::vec2(0.1f), glm::vec2(60,20), panel2);
    button1->InitTexture(gui_shader, texture3);

    Button* button2 = canvas->NewButton(glm::vec2(0.6f, 0.1f), glm::vec2(60,20), panel2);
    button2->InitTexture(gui_shader, texture3);
    button2->Disable();

    std::function<void(void*)> SwitchButtons = 
        [button1, button2](void* num) {
            std::cout << *(int*)num << std::endl;
            if (button1->IsDisabled()) {
                button1->Enable();
                button2->Disable();
            } else {
                button1->Disable();
                button2->Enable();
            }
        };
    int num1 = 123;
    int num2 = 321;
    button1->SetOnClick( SwitchButtons, (void*)&num1 );
    button2->SetOnClick( SwitchButtons, (void*)&num2 );

    Button* button3 = canvas->NewButton(glm::vec2(0.4f, 0.5f), glm::vec2(60,20), panel1);
    button3->InitTexture(gui_shader, texture3);
    //panel1->SwapChildrenOrder(panel1->GetChildCount()-1, 0);

    Button* button4 = canvas->NewButton(glm::vec2(0.6f, 0.7f), glm::vec2(60,20), panel2);
    button4->InitTexture(gui_shader, texture3);

    std::function<void(void*)> TogglePanel = 
        [](void* p) { 
            Panel* panel = static_cast<Panel*>(p);
            if (!panel->IsDisabled()) {
                panel->Disable();
            } else {
                panel->Enable();
            }
        };
    button3->SetOnClick( TogglePanel, panel2 ); 
    button4->SetOnClick( TogglePanel, panel2 );
    
    // initlialize textrenderer with font.

    // 
    DrawableGameObject* go1 = new DrawableGameObject("GO 1", texture2, shader1);  
    DrawableGameObject* go2 = new DrawableGameObject("GO 1", texture1, shader1);  

    go1->GetTransform()->GetScale()->x *= 10;
    go1->GetTransform()->GetScale()->y *= 10;

    
    // Input handling
    SDL_Event e;
    const Uint8* keystate = SDL_GetKeyboardState(nullptr); // holds a snapshot of the keyboard.
    bool isRunning = true;

    InputHandler* input_handler = new InputHandler(keystate, cam, window, canvas);

    float delta_time;    
    float fps;
    char fps_string[10];


    while(isRunning) 
    {
        window->Clear(0.0f, 0.2f, 0.0f, 1.0f);

        clock.tick();
        delta_time = clock.delta_time / 1000.0f; // in seconds.


        fps = 1.0f / delta_time;
        sprintf(fps_string, "FPS: %d", (int)fps);
        label1->ConfigText(fps_string, FS_18, glm::vec2(0));


        //// HANDLE INPUT HERE
        try {
            input_handler->HandleInput(&e, delta_time, &isRunning);
        }
        catch ( const GUI::GUIException &e ) {
            std::cout << "Error in GUI while running: " << e.what() << std::endl;
            return 1;
        }
        /// END INPUT HANDLING


        go1->DrawSprite();
        go2->DrawSprite();

        panel1->Draw(cam);
        
        window->SwapBuffers();

        SDL_Delay(10);
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
