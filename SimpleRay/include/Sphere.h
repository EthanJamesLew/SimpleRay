
#ifndef SPHERE_H
#define SPHERE_H


#include "Vector3d.h"

typedef Vector3d<float> vec3f;

class Sphere
{
public:
	vec3f center;
	float radius, radius2;
	vec3f surfaceColor, emissionColor;
	float transparency, reflection;
	
	Sphere(
		const vec3f &c,
		const float &r,
		const vec3f &sc,
		const float &refl = 0,
		const float &transp = 0,
		const vec3f &ec = 0);

	bool intersect(const vec3f &rayorig, const vec3f &raydir, float &t0, float &t1);
	vec3f getCenter(){ return center; }
};
#endif