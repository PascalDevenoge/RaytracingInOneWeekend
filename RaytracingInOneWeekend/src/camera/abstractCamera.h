#pragma once

#include <vector>

class ray;

class abstractCamera {
public:
	virtual std::vector<ray> getRaysForPixel(double u, double v) const = 0;
	virtual ~abstractCamera() {};
};