#pragma once

#include "../hittable.h"
#include "../aabb.h"

class sphere : public hittable {
public:
	sphere(point3 cen, double r, shared_ptr<abstractMaterial> material) : center(cen), radius(r), material(material) {};

	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;
	virtual bool boundingBox(double startTime, double stopTime, aabb& outputBox) const override;

	point3 center;
	double radius;
	shared_ptr<abstractMaterial> material;

private:
	static void getSphereUV(const point3& p, double& u, double& v) {
		auto theta = acos(-p.y());
		auto phi = atan2(-p.z(), p.x()) + pi;

		u = phi / (2 * pi);
		v = theta / pi;
 	}
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
	getSphereUV(outwardNormal, rec.u, rec.v);
	rec.material = material;

	return true;
}

bool sphere::boundingBox(double startTime, double stopTime, aabb& outputBox) const {
	outputBox = aabb(
		center - vec3(radius, radius, radius),
		center + vec3(radius, radius, radius)
	);
	return true;
}
