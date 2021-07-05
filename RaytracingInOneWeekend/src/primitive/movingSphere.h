#pragma once

#include "../hittable.h"
#include "../vec3.h"
#include "../ray.h"
#include "../material/abstractMaterial.h"
#include "../hitRecord.h"
#include "../aabb.h"

class movingSphere : public hittable {
public:
	movingSphere(
		point3 center0,
		point3 center1,
		double startTime,
		double stopTime,
		double radius,
		shared_ptr<abstractMaterial> material
	) : center0(center0), center1(center1), startTime(startTime), stopTime(stopTime), radius(radius), material(material) {};

	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;
	virtual bool boundingBox(double startTime, double stopTime, aabb& outputBox) const override;
	point3 center(double time) const;

	point3 center0, center1;
	double startTime, stopTime;
	double radius;
	shared_ptr<abstractMaterial> material;

private:
	static void getSphereUV(const point3& p, double& u, double& v);
};

point3 movingSphere::center(double time) const {
	return center0 + ((time - startTime) / (stopTime - startTime)) * (center1 - center0);
}

bool movingSphere::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
	vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().lengthSquared();
	auto halfB = dot(oc, r.direction());
	auto c = oc.lengthSquared() - radius * radius;

	auto discriminant = halfB * halfB - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-halfB - sqrtd) / a;
	if (root < tMin || root > tMax) {
		root = (-halfB - sqrtd) / a;
		if (root < tMin || root > tMax) return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	auto outwardNormal = (rec.p - center(r.time())) / radius;
	rec.setFaceNormal(r, outwardNormal);
	getSphereUV(outwardNormal, rec.u, rec.v);
	rec.material = material;

	return true;
}

bool movingSphere::boundingBox(double startTime, double stopTime, aabb& outputBox) const {
	aabb box0(
		center(startTime) - vec3(radius, radius, radius),
		center(startTime) + vec3(radius, radius, radius)
	);
	aabb box1(
		center(stopTime) - vec3(radius, radius, radius),
		center(stopTime) + vec3(radius, radius, radius)
	);
	outputBox = aabb::surroundingBox(box0, box1);
	return true;
}

void movingSphere::getSphereUV(const point3& p, double& u, double& v) {
	auto theta = acos(-p.y());
	auto phi = atan2(-p.z(), p.x()) + pi;

	u = phi / (2 * pi);
	v = theta / pi;
}