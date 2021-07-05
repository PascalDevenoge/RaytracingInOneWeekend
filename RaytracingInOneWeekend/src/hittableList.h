#pragma once

#include <vector>
#include <memory>

#include "hittable.h"
#include "hitRecord.h"
#include "aabb.h"

using std::shared_ptr;
using std::make_shared;

class hittableList : public hittable {
public:
	hittableList() {}
	hittableList(shared_ptr<hittable> object) { add(object); }

	std::vector<shared_ptr<hittable>> objects;

	void clear() { objects.clear(); }
	void add(shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;
	virtual bool boundingBox(double startTime, double stopTime, aabb& outputBox) const override;
};

bool hittableList::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
	hitRecord tempRec;
	bool hitAnything = false;
	auto closestSoFar = tMax;

	for (const auto& object : objects) {
		if (object->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

bool hittableList::boundingBox(double startTime, double stopTime, aabb& outputBox) const {
	if (objects.empty()) return false;

	aabb tempBox;
	bool firstBox = true;

	for (const auto& object : objects) {
		if (!object->boundingBox(startTime, stopTime, tempBox)) return false;
		outputBox = firstBox ? tempBox : aabb::surroundingBox(outputBox, tempBox);
		firstBox = false;
	}
	return true;
}
