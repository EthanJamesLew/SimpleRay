#include "..\include\RayWindow.h"
#include <iostream>
#include <ctime>
#include <ratio>
#include <sstream>

RayWindow::RayWindow(int x, int y) : _width(x), _height(y)
{
	_window = nullptr;
	_renderer = nullptr;
	_texture = nullptr;
	_raytracer = nullptr;
	pixels = nullptr;
}


RayWindow::~RayWindow()
{
	delete[] pixels;
	SDL_DestroyTexture(_texture);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void RayWindow::init()
{
	_raytracer = new Raytracer(_width, _height);

	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Simple Ray",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0);

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	_texture = SDL_CreateTexture(_renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
	
}

void RayWindow::processEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			this->~RayWindow();
		}
	}
}

void RayWindow::run()
{
	while (true)
	{

		_begin = high_resolution_clock::now();
		_raytracer->render(pixels);
		_end = high_resolution_clock::now();
		std::chrono::duration<double>_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(_end - _begin);

		std::stringstream str;

		str <<"Simple Ray - " << 1.0/_elapsed.count() << " FPS";
		SDL_SetWindowTitle(_window, str.str().c_str());

		SDL_UpdateTexture(_texture, NULL, pixels, _width * sizeof(Uint32));
	
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _texture, NULL, NULL);
		SDL_RenderPresent(_renderer);

		processEvent();
	}
}