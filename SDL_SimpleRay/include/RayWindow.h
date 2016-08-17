#pragma once
#include <SDL2\SDL.h>
#include "Raytracer.h"
#include <chrono>

typedef  std::chrono::high_resolution_clock::time_point timeC;
using std::chrono::high_resolution_clock;

class RayWindow
{
public:
	RayWindow(int x, int y);
	~RayWindow();

	void init();
	void processEvent();
	void run();

	Uint32 *pixels;

private:
	int _width;
	int _height;

	SDL_Window * _window;
	SDL_Renderer * _renderer;
	SDL_Texture * _texture;

	Raytracer* _raytracer;

	timeC _begin;
	timeC _end;
	std::chrono::duration<double> _elapsed;
	
	
};

