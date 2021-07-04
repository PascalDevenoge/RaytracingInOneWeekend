#pragma once

#include "abstractMaterial.h"

class metal : public abstractMaterial {
public:
	metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
		vec3 reflected = vec3::reflect(vec3::normalize(rIn.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * vec3::randomInUnitSphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

	color albedo;
	double fuzz;
};