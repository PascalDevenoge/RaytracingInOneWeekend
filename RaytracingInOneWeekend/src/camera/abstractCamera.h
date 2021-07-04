#pragma once

#include <vector>

#include "../ray.h"

class abstractCamera {
public:
	virtual std::vector<ray> getRaysForPixel(double u, double v) = 0;
	virtual ~abstractCamera() {};
};