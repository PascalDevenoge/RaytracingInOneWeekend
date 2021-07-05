#pragma once

#include "../vec3.h"

class texture {
public:
	virtual color value(double u, double v, const point3& p) const = 0;
};