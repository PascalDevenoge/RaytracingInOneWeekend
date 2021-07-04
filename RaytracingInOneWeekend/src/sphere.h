#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere(point3 cen, double r, shared_ptr<abstractMaterial> material) : center(cen), radius(r), material(material) {};

	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;

	point3 center;
	double radius;
	shared_ptr<abstractMaterial> material;
};

bool sphere::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
	vec3 oc = r.origin() - center;
	auto a = r.direction().lengthSquared();
	auto halfB = dot(oc, r.direction());
	auto c = oc.lengthSquared() - radius * radius;

	auto discriminant = halfB * halfB - a * c;
	if (discriminant < 0) return false;

	auto sqrtd = sqrt(discriminant);

	auto root = (-halfB - sqrtd) / a;
	if (root < tMin || root > tMax) {
		root = (-halfB + sqrtd) / a;
		if (root < tMin || root > tMax) return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outwardNormal = (rec.p - center) / radius;
	rec.setFaceNormal(r, outwardNormal);
	rec.material = material;

	return true;
}