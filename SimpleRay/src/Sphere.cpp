#include "..\include\Sphere.h"

Sphere::Sphere(
	const vec3f &c,
	const float &r,
	const vec3f &sc,
	const float &refl,
	const float &transp,
	const vec3f &ec) :
	center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec),
	transparency(transp), reflection(refl) {}

bool Sphere::intersect(const vec3f &rayorig, const vec3f &raydir, float &t0, float &t1)
{
	vec3f l = center - rayorig;
	float tca = l.dot(raydir);
	if (tca < 0) return false;
	float d2 = l.dot(l) - tca * tca;
	if (d2 > radius2) return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}