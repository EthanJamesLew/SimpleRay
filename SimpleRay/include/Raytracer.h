#pragma once

#ifdef _WIN32
#define DLL  __declspec( dllexport )
#else
#define DLL 
#endif

#ifndef RAYTRACER_H
#define RAYTRACER_H 

#include "Vector3d.h"
#include "Sphere.h"
#include <SDL2\SDL.h>
#include <vector>

typedef Vector3d<float> vec3f;
typedef Vector3d<float> rgbf;

enum class Shaders {DIFFUSE, GLOSSY, REFRACTIVE, NORMAL, Z};

class DLL Raytracer
{
public:
	Raytracer(int x, int y);
	~Raytracer();

	void render(Uint32*& pixels);


private:
	rgbf _trace(const vec3f &rayorig, const vec3f &raydir, const int &depth);
	int _width;
	int _height;
	//Hard-coded for now
	std::vector<Sphere> _sph;
	vec3f* _pixel;
	vec3f* _image;

};
#endif
