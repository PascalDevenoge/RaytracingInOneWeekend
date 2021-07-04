#pragma once

#include "abstractCamera.h"

class depthOfFieldCamera : public abstractCamera {
public:
	depthOfFieldCamera(
		point3 position,
		point3 lookAt,
		vec3 up,
		double fov,
		double aspectRatio,
		double aperture,
		double focusDistance,
		int samplesPerPixel
	) : samplesPerPixel(samplesPerPixel) {
		auto theta = degreesToRadians(fov);
		auto h = tan(theta / 2);
		auto viewportHeight = 2.0 * h;
		auto viewportWidth = aspectRatio * viewportHeight;

		w = vec3::normalize(position - lookAt);
		u = vec3::normalize(cross(up, w));
		v = cross(w, u);

		cameraPosition = position;
		horizontalSpan = focusDistance * viewportWidth * u;
		verticalSpan = focusDistance * viewportHeight * v;
		upperLeftCorner = cameraPosition + (verticalSpan / 2) - (horizontalSpan / 2) - focusDistance * w;

		lensRadius = aperture / 2;
	}

	virtual std::vector<ray> getRaysForPixel(double s, double t) override {
		std::vector<ray> rays;
		for (int i = 0; i < samplesPerPixel; i++) {
			vec3 rd = lensRadius * vec3::randomInUnitDisk();
			vec3 offset = u * rd.x() + v * rd.y();

			ray sample(cameraPosition + offset, upperLeftCorner + s * horizontalSpan - t * verticalSpan - cameraPosition - offset);

			rays.push_back(sample);
		}
		return rays;
	}

private:
	point3 cameraPosition;
	point3 upperLeftCorner;
	vec3 horizontalSpan;
	vec3 verticalSpan;
	vec3 u, v, w;
	double lensRadius;
	int samplesPerPixel;
};