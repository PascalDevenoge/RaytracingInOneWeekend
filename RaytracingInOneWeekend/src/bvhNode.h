#pragma once

#include <memory>

#include "hittable.h"
#include "hittableList.h"
#include "aabb.h"

class bvhNode : public hittable {
public:
	bvhNode();
	bvhNode(const hittableList& list, double startTime, double stopTime)
		: bvhNode(list.objects, 0, list.objects.size(), startTime, stopTime)
	{}

	bvhNode(
		const std::vector<shared_ptr<hittable>>& srcObjects,
		size_t start,
		size_t end,
		double startTime,
		double stopTime
	);

	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;
	virtual bool boundingBox(double startTime, double stopTime, aabb& outputBox) const override;

	std::shared_ptr<hittable> left;
	std::shared_ptr<hittable> right;
	aabb box;
};

bool boxXCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);
bool boxYCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);
bool boxZCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);

inline bvhNode::bvhNode(
	const std::vector<std::shared_ptr<hittable>>& srcObjects,
	size_t start,
	size_t end,
	double startTime,
	double stopTime
) {
	auto objects = srcObjects;

	int axis = randomInt(0, 2);
	auto comparator = (axis == 0) ? boxXCompare
		: (axis == 1) ? boxYCompare
		: boxZCompare;

	size_t objectSpan = end - start;

	if (objectSpan == 1) {
		left = right = objects[start];
	} else if (objectSpan == 2) {
		if (comparator(objects[start], objects[start + 1])) {
			left = objects[start];
			right = objects[start + 1];
		} else {
			left = objects[start + 1];
			right = objects[start];
		}
	} else {
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		auto mid = start + objectSpan / 2;
		left = make_shared<bvhNode>(objects, start, mid, startTime, stopTime);
		right = make_shared<bvhNode>(objects, mid, end, startTime, stopTime);
	}

	aabb boxLeft, boxRight;

	if (!left->boundingBox(startTime, stopTime, boxLeft)
		|| !right->boundingBox(startTime, stopTime, boxRight)) {
		std::cerr << "No bounding box in bvhNode constructor\n";
	}

	box = aabb::surroundingBox(boxLeft, boxRight);
}

inline bool bvhNode::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
	if (!box.hit(r, tMin, tMax)) return false;

	bool hitLeft = left->hit(r, tMin, tMax, rec);
	bool hitRight = right->hit(r, tMin, hitLeft ? rec.t : tMax, rec);

	return hitLeft || hitRight;
}

inline bool bvhNode::boundingBox(double startTime, double stopTime, aabb& outputBox) const {
	outputBox = box;
	return true;
}

inline bool boxCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, int axis) {
	aabb boxA, boxB;

	if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
		std::cerr << "No bounding box in bvhNode constructor\n";

	return boxA.min()[axis] < boxB.min()[axis];
}

bool boxXCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
	return boxCompare(a, b, 0);
}

bool boxYCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
	return boxCompare(a, b, 1);
}

bool boxZCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
	return boxCompare(a, b, 2);
}