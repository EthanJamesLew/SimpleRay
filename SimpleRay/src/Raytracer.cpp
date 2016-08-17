#include "..\include\Raytracer.h"

#include <fstream>
#include <algorithm>
#include <omp.h>

#if defined __linux__ || defined __APPLE__ 
#else 
#define M_PI 3.141592653589793 
#define INFINITY 1e8 
#endif 

Raytracer::Raytracer(int x, int y) : _width(x), _height(y)
{
	_image = new vec3f[_width * _height];
	Sphere sp1 = (Sphere(vec3f(0.0f, 0.0f, -20.0f), 2, vec3f(1.0f, .32f, .36f), 1, 0.5f));
	_sph.push_back((sp1));
	_sph.push_back(Sphere(vec3f(3.0f, 0.0f, -10.0f), 3, vec3f(1.0f, .32f, .36f), 1, 0.5f));
	_sph.push_back(Sphere(vec3f(-3.0f, 0.0f, -5.0f), 1, vec3f(1.0f, .32f, .36f), 1, 0.5f));
	_pixel = _image;

	omp_set_num_threads(omp_get_max_threads());
}


Raytracer::~Raytracer()
{
	delete[] _image;
	delete[] _pixel;
}

void Raytracer::render(Uint32*& pixels)
{
	_image = new vec3f[_width * _height];
	_pixel = _image;

	pixels = new Uint32[_width * _height];
	memset(pixels, 255, _width * _height * sizeof(Uint32));

	//Camera Params
	float invWidth = 1 / float(_width), invHeight = 1 / float(_height);
	float fov = 30, aspectratio = _width / float(_height);
	float angle = tan(M_PI * 0.5 * fov / 180.);

	// Trace rays

	for (unsigned y = 0; y < _height; ++y) {
		for (unsigned x = 0; x < _width; ++x, ++_pixel) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			vec3f raydir(xx, yy, -1);
			raydir.normalize();
			*_pixel = _trace(vec3f(0.0), raydir, 0.0);
		}
	}
	
#pragma omp parallel 
	{
		int idx = omp_get_thread_num();
		int max = omp_get_num_threads();
		double begin = (double(idx) / (double(max)))*_width * _height;
		double end = (double(idx+1) / (double(max)))*_width * _height;
		for (unsigned i = begin; i < end; ++i) {
			Uint32 pix = 0;
			pix = (unsigned char)(std::min(float(1), _image[i].x) * 255) << 16;
			pix += (unsigned char)(std::min(float(1), _image[i].y) * 255) << 8;
			pix += (unsigned char)(std::min(float(1), _image[i].z) * 255) << 0;
			pixels[i] = pix;
		}
		delete[] _image;
	}

}

rgbf Raytracer::_trace(const vec3f &rayorig, const vec3f &raydir, const int &depth)
{
	//1 BEGIN
	Sphere* curSph = nullptr;
	float tnear = INFINITY; float t0 = INFINITY; float t1 = INFINITY;
	for (unsigned i = 0; i < _sph.size(); ++i)
	{
		if (_sph[i].intersect(rayorig, raydir, t0, t1))
		{
			if (t0 < 0) t0 = t1;
			if (t0 < tnear)
			{
				tnear = t0;
				curSph = &_sph[i];
			}
		}
	}
	//1 END

	//2 CASE BACKGROUND
	if (!curSph) return rgbf(2.0f);

	//3 GET NORMAL
	vec3f surfaceColor = 0;
	vec3f phit = rayorig + raydir * tnear; 
	vec3f nhit = phit - curSph->center;
	nhit.normalize();

	float bias = 1e-4;
	bool inside = false;
	if (raydir.dot(nhit) > 0) nhit = -nhit, inside = true;

	float facingratio = -raydir.dot(nhit);

	return facingratio;
}