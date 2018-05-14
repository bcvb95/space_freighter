#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <display.h>
#include <camera.h>
#include <gameobject.h>
#include <input_handler.h>
#include "mainsim.h"
#include "world_go.h"
#include <gui_objects.h>
#include "text_renderer.h"
 
#define WIDTH 800
#define HEIGHT 500


int main(int argc, char** argv)
{
    // Graphics
    Display* window = new Display(WIDTH, HEIGHT, argv[0]+2);
    Camera* cam = new Camera(glm::vec3(0,0,0), 0, window);
    GUI::Canvas* canvas = new GUI::Canvas(window);

    cam->SetZoom(3.2f, false);
    Clock clock;

    Texture* planet_tex = new Texture("../res/planet_tex1.png", false);
    Texture* star_tex = new Texture("../res/star_tex1.png", false);
    Texture* tex1 = new Texture("../res/tex.png", true);

    TextShader* text_shader = new TextShader("../res/textShader", cam);
    TextRenderer* text_renderer = new TextRenderer(text_shader, "../res/data-latin.ttf");
    BasicShader* shader = new BasicShader("../res/basicShader", cam);
    GUI_Shader* gui_shader = new GUI_Shader("../res/gui_shader", cam);

    GUI::Panel* panel1 = canvas->NewPanel(glm::vec2(0.0f, 0.0f), glm::vec2(100, 50));
    GUI::Label* fps_label = canvas->NewLabel(glm::vec2(0), panel1,text_renderer, "FPS placeholder", FS_18);
    panel1->InitTexture(gui_shader, tex1);

    WorldGO* planet_GOs[Simulation::MAX_WORLDS]; 
    DrawableGameObject* star_GOs[Simulation::MAX_SOLARSYSTEMS];
    //= new DrawableGameObject("planet1", planet_tex, shader);

    // Simulation
    unsigned int simulation_seed = 123454321;
    int universe_size = 949;
    int dt = 5;

    Simulation::MainSim* sim;
    try {
        sim = new Simulation::MainSim();
        sim->Init(simulation_seed, universe_size);
    } 
    catch ( const Simulation::GeneratorException &e ) {
        std::cout << "Error in Generator while starting up: " << e.what() << std::endl;
        return 1;
    }
    catch ( const Simulation::UniverseException &e ) {
        std::cout << "Error in Universe while starting up: " << e.what() << std::endl;
        return 1;
    }
    catch ( const Simulation::SimulationException &e) {
        std::cout << "Error in main simulation while starting up: " << e.what() << std::endl;
        return 1;
    }

    // Create gameobjects
    Simulation::Universe* universe = sim->getUniverse();
    Simulation::World** worlds = universe->getWorlds();
    Simulation::SolarSystem** solar_systems = universe->getSolarSystems();

    for (int i=0; i < universe->getSolarSystemCount(); i++) {
        star_GOs[i] = new DrawableGameObject("sun " + i, star_tex, shader);
        Transform* star_transform = star_GOs[i]->GetTransform();
        glm::vec2 starpos = solar_systems[i]->getPosition();
        star_transform->SetPos(glm::vec3(starpos.x, starpos.y, 0));
        star_transform->SetScale(glm::vec3(5, 5, 1));
    }

    for (int i=0; i < universe->getWorldCount(); i++) {
        planet_GOs[i] = new WorldGO(worlds[i]->getName(), planet_tex, shader, worlds[i]);
        Transform* transform = planet_GOs[i]->GetTransform();
        transform->SetScale(glm::vec3(2, 2, 1));
    }

    // Main loop
    SDL_Event e;
    bool isRunning = true;
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    InputHandler* input_handler = new InputHandler(keystate, cam, window, canvas);


    float delta_time;
    float time_mul = 1.0f;

    float fps;
    char fps_string[10];
    
    while(isRunning) 
    {
        clock.tick();
        delta_time = clock.delta_time / 1000.0; // in seconds.

        fps = 1.0f / delta_time;
        sprintf(fps_string, "FPS: %d", (int)fps);

        fps_label->ConfigText(fps_string, FS_18, glm::vec2(0));

        window->Clear(0.0f, 0.0f, 0.0f, 1.0f);

        input_handler->HandleInput(&e, delta_time, &isRunning, &time_mul);

        try {
            sim->Update(delta_time * time_mul);
        }
        catch ( const Simulation::GeneratorException &e ) {
            std::cout << "Error in Generator while running: " << e.what() << std::endl;
            return 1;
        }
        catch ( const Simulation::UniverseException &e ) {
            std::cout << "Error in Universe while running: " << e.what() << std::endl;
            return 1;
        }
        catch ( const Simulation::SimulationException &e) {
            std::cout << "Error in main simulation while running: " << e.what() << std::endl;
            return 1;
        }
        // DRAW
        for (int i=0; i < universe->getSolarSystemCount(); i++) {
            star_GOs[i]->DrawSprite();
        }
        for (int i=0; i < universe->getWorldCount(); i++) {
            planet_GOs[i]->DrawSprite();
        }
        // GUI
        

        panel1->Draw(cam);

        window->SwapBuffers();
        SDL_Delay(17);
    } 
    
    for (int i=0; i < universe->getWorldCount(); i++) {
        delete planet_GOs[i];
    }
    for (int i=0; i < universe->getSolarSystemCount(); i++) {
        delete star_GOs[i];
    }

    delete window;
    delete cam;
    delete sim;
}
