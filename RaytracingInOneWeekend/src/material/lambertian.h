#pragma once

#include "abstractMaterial.h"
#include "../texture/solidColor.h"

class lambertian : public abstractMaterial {
public:
	lambertian(const color& a) : albedo(make_shared<solidColor>(a)) {}
	lambertian(std::shared_ptr<texture> a) : albedo(a) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
		auto scatterDirection = rec.normal + vec3::randomUnitVector();

		if (scatterDirection.nearZero())
			scatterDirection = rec.normal;

		scattered = ray(rec.p, scatterDirection, rIn.time());
		attenuation = albedo->value(rec.u, rec.v, rec.p);
		return true;
	}

	shared_ptr<texture> albedo;
};