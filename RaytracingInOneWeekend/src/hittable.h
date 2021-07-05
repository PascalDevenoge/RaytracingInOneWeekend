#pragma once

class ray;
struct hitRecord;
class aabb;

class hittable {
public:
	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const = 0;
	virtual bool boundingBox(double startTime, double stopTime, aabb& outputBox) const = 0;
};