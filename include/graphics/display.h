#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

	virtual ~Display();
	SDL_Window* GetSDLWindow() {return this->m_window;}

	int GetWindowWidth() {return m_windowWidth;}
	int GetWindowHeight() {return m_windowHeight;}
	float GetWindowAspect() {return m_windowAspect;}

protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	int m_windowWidth;
	int m_windowHeight;
	float m_windowAspect;
};

struct Clock
{
	uint32_t last_tick_time = 0;
	float delta_time = 0.0f;

	void tick()
	{
		uint32_t tick_time = SDL_GetTicks();
		delta_time = (float)(tick_time - last_tick_time);
		last_tick_time = tick_time;
	}
};


#endif
