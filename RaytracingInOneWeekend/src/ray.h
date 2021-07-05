#pragma once

#include "vec3.h"

class ray {
public:
	point3 orig;
	vec3 dir;
	double t;

	ray() {}
	ray(const point3& origin, const vec3& direction, double time = 0.0)
		: orig(origin), dir(direction), t(time)
	{}

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }
	double time() const { return t; }

	point3 at(const double t) const {
		return orig + t * dir;
	}
};