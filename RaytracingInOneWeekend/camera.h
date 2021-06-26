#pragma once

#include "utilities.h"

class camera {
public:
	camera() {
		auto aspectRatio = 16.0 / 9.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = aspectRatio * viewportHeight;
		auto focalLength = 1.0;

		origin = point3(0, 0, 0);
		horizontal = vec3(viewportWidth, 0.0, 0.0);
		vertical = vec3(0.0, viewportWidth, 0.0);
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);
	}

	camera(double viewportHeight, double viewportWidth, double focalLength, antiAliasingMode AAMode, int numOfSamples = 1) {
		position = point3(0, 0, 0);
		horizontal = vec3(viewportWidth, 0, 0);
		vertical = vec3(0, viewportHeight, 0);
		screenUpperLeftCorner = origin + vec3(0, 0, -focalLength) + vertical / 2 - horizontal / 2;
		numberOfSamples = numOfSamples;
		aaMode = AAMode;
	}

	ray getRay(double u, double v) const {
		return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

private:
	point3 position;
	point3 screenUpperLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	int numberOfSamples;
	antiAliasingMode aaMode;

	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

enum class antiAliasingMode {
	NONE,
	RANDOM_MULTISAMPLE
};