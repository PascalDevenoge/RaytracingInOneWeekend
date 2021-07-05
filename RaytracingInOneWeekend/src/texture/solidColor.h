#pragma once

#include "texture.h"

class solidColor : public texture {
public:
	solidColor(color c) : colorValue(c) {}
	solidColor(double red, double green, double blue)
		: solidColor(color(red, green, blue)) {}

	virtual color value(double u, double v, const vec3& p) const override {
		return colorValue;
	}

private:
	color colorValue;
};