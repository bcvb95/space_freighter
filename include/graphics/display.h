#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

	virtual ~Display();
protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

struct Clock
{
	uint32_t last_tick_time = 0;
	float delta_time = 0;

	void tick()
	{
		uint32_t tick_time = SDL_GetTicks();
		delta_time = (float)(tick_time - last_tick_time);
		last_tick_time = tick_time;
	}
};


#endif
