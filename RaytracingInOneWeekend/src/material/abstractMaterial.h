#pragma once

#include "../utilities.h"

struct hitRecord;

class abstractMaterial {
public:
	virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const = 0;
	virtual ~abstractMaterial() {};
};