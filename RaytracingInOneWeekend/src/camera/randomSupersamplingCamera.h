#pragma once

#include "abstractCamera.h"

class randomSupersamplingCamera : abstractCamera {
public:
	randomSupersamplingCamera(
		point3 position,
		point3 lookAt,
		vec3 up,
		double fov,
		double aspectRatio,
		int numOfPixelsVert,
		int numOfPixelsHor,
		int samplesPerPixel
	) : samplesPerPixel(samplesPerPixel) {
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
		verticalPixelSize = viewportHeight / numOfPixelsVert;
		horizontalPixelSize = viewportWidth / numOfPixelsHor;
	}

	virtual std::vector<ray> getRaysForPixel(double u, double v) const override {
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