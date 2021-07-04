#pragma once

#include "abstractMaterial.h"

class lambertian : public abstractMaterial {
public:
	lambertian(const color& a) : albedo(a) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
		auto scatterDirection = rec.normal + vec3::randomUnitVector();

		if (scatterDirection.nearZero())
			scatterDirection = rec.normal;

		scattered = ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}

	color albedo;
};