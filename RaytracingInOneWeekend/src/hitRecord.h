#pragma once

#include "ray.h"

class abstractMaterial;

struct hitRecord {
	point3 p;
	vec3 normal;
	shared_ptr<abstractMaterial> material;
	double t;
	double u, v;
	bool frontFace;
	color diffuseAlbedo;

	inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};