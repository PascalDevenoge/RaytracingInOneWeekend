#pragma once

#include "abstractCamera.h"
#include "../utilities.h"

class randomSupersamplingCamera : abstractCamera {
public:
	randomSupersamplingCamera(double viewportHeight, double viewportWidth, double focalLength, int numOfPixelsVert, int numOfPixelsHor, int samplesPerPixel) : samplesPerPixel(samplesPerPixel) {
		cameraPosition = vec3(0, 0, 0);
		horizontalSpan = vec3(viewportWidth, 0, 0);
		verticalSpan = vec3(0, viewportHeight, 0);
		focalVec = vec3(0, 0, -focalLength);
		upperLeftCorner = cameraPosition + focalVec + (verticalSpan / 2) - (horizontalSpan / 2);
		verticalPixelSize = viewportHeight / numOfPixelsVert;
		horizontalPixelSize = viewportWidth / numOfPixelsHor;
	}

	virtual std::vector<ray> getRaysForPixel(double u, double v) override {
		std::vector<ray> rays;
		for (int i = 0; i < samplesPerPixel; i++) {
			vec3 centerScreenPosition = upperLeftCorner + u * horizontalSpan - v * verticalSpan;
			vec3 screenPosition = centerScreenPosition + vec3(0, verticalPixelSize, 0) * randomDouble(-0.5, 0.5)
				+ vec3(horizontalPixelSize, 0, 0) * randomDouble(-0.5, 0.5);
			rays.push_back(ray(cameraPosition, screenPosition - cameraPosition));
		}
		return rays;
	}

private:
	vec3 cameraPosition;
	vec3 horizontalSpan;
	vec3 verticalSpan;
	vec3 focalVec;
	vec3 upperLeftCorner;
	double verticalPixelSize;
	double horizontalPixelSize;
	int samplesPerPixel;
};