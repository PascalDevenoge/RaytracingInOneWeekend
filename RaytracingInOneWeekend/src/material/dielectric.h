#pragma once

class dielectric : public abstractMaterial {
public:
	dielectric(double ior) : ior(ior) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
		attenuation = color(1.0, 1.0, 1.0);
		double refractionRatio = rec.frontFace ? (1.0 / ior) : ior;
		vec3 unitDirection = vec3::normalize(rIn.direction());
		double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
		double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0;
		
		vec3 direction;
		if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble()) {
			direction = vec3::reflect(unitDirection, rec.normal);
		} else {
			direction = vec3::refract(unitDirection, rec.normal, refractionRatio);
		}

		scattered = ray(rec.p, direction, rIn.time());
		return true;
	}

	double ior;

private:
	static double reflectance(double cosine, double refIndex) {
		auto r0 = (1 - refIndex) / (1 + refIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};