#pragma once

#include "texture.h"
#include "solidColor.h"

class checkerTexture : public texture {
public:
	checkerTexture(std::shared_ptr<texture> even, std::shared_ptr<texture> odd)
		: odd(odd), even(even) { }

	checkerTexture(color c1, color c2)
		: even(make_shared<solidColor>(c1)), odd(make_shared<solidColor>(c2)) { }

	virtual color value(double u, double v, const point3& p) const override {
		auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

		if (sines < 0) return odd->value(u, v, p);
		else return even->value(u, v, p);
	}

	std::shared_ptr<texture> odd;
	std::shared_ptr<texture> even;
};