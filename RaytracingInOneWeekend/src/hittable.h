#pragma once

#include "ray.h"
#include "material/abstractMaterial.h"

struct hitRecord {
	point3 p;
	vec3 normal;
	shared_ptr<abstractMaterial> material;
	double t;
	bool frontFace;
	color diffuseAlbedo;

	inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const = 0;
};