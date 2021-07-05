#pragma once

#include "abstractCamera.h"

class basicCamera : abstractCamera {
public:
	double minVert = std::numeric_limits<double>::max();
	double maxVert = std::numeric_limits<double>::min();
	double minHor = std::numeric_limits<double>::max();
	double maxHor = std::numeric_limits<double>::min();

	basicCamera(point3 position, point3 lookAt, vec3 up, double fov, double aspectRatio) {
		auto theta = degreesToRadians(fov);
		auto h = tan(theta / 2);
		auto viewportHeight = 2.0 * h;
		auto viewportWidth = aspectRatio * viewportHeight;
		auto focalLength = 1.0;

		auto w = vec3::normalize(position - lookAt);
		auto u = vec3::normalize(cross(up, w));
		auto v = cross(w, u);

		cameraPosition = position;
		horizontalSpan = viewportWidth * u;
		verticalSpan = viewportHeight * v;
		upperLeftCorner = cameraPosition + (verticalSpan / 2) - (horizontalSpan / 2) - w;
	}

	virtual std::vector<ray> getRaysForPixel(double u, double v) const override {
		std::vector<ray> rays;
		vec3 screenPosition = upperLeftCorner + u * horizontalSpan - v * verticalSpan;
 		rays.push_back(ray(cameraPosition, screenPosition - cameraPosition));
		return rays;
	}

private:
	vec3 cameraPosition;
	vec3 horizontalSpan;
	vec3 verticalSpan;
	vec3 focalVec;
	vec3 upperLeftCorner;
};
