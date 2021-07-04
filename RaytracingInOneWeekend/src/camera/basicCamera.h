#pragma once

#include "abstractCamera.h"
#include "../utilities.h"

class basicCamera : abstractCamera {
public:
	double minVert = std::numeric_limits<double>::max();
	double maxVert = std::numeric_limits<double>::min();
	double minHor = std::numeric_limits<double>::max();
	double maxHor = std::numeric_limits<double>::min();


	basicCamera(double viewportHeight, double viewportWidth, double focalLength) {
		cameraPosition = vec3(0, 0, 0);
		horizontalSpan = vec3(viewportWidth, 0, 0);
		verticalSpan = vec3(0, viewportHeight, 0);
		focalVec = vec3(0, 0, -focalLength);
		upperLeftCorner = cameraPosition + focalVec + (verticalSpan / 2) - (horizontalSpan / 2);
	}

	virtual std::vector<ray> getRaysForPixel(double u, double v) override {
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
