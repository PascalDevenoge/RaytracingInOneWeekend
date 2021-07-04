#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

#include "hittableList.h"
#include "color.h"
#include "sphere.h"
#include "camera/basicCamera.h"
#include "camera/randomSupersamplingCamera.h"
#include "utilities.h"

color rayColor(const ray& r, const hittableList& world);
void writeColorToBuffer(color color, int pixelNum, uint8_t* buffer);
void writeImageBufferToFile(const uint8_t* imageData, const int imageWidth, const int imageHeight);

int main() {

	// Image parameters
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 200;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const double focalLength = 1.0;

	// Scene description
	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera setup
	// basicCamera camera(2.0, 2.0 * aspectRatio, focalLength);
	randomSupersamplingCamera camera(2.0, 2.0 * aspectRatio, focalLength, imageHeight, imageWidth, 100);

	// Pixel buffer
	uint8_t* image_data = new uint8_t[imageWidth * imageHeight * 3];

	// Render loop
	for (int row = 0; row < imageHeight; row++) {
		std::cout << "\nRows left: " << imageHeight - row << ' ' << std::flush;

		for (int collumn = 0; collumn < imageWidth; collumn++) {
			color pixelColor(0, 0, 0);
			std::vector<ray> sampleRays = camera.getRaysForPixel((double) collumn / imageWidth, (double) row / imageHeight);
			for (const auto& sample : sampleRays) {
				pixelColor += rayColor(sample, world);
			}
			pixelColor /= static_cast<double>(sampleRays.size());
			writeColorToBuffer(pixelColor, row * imageWidth + collumn, image_data);
		}
	}

	// Write out buffer
	writeImageBufferToFile(image_data, imageWidth, imageHeight);
	delete[] image_data;
	std::cout << "\nFinished";
}

color rayColor(const ray& r, const hittableList& world) {
	hitRecord record;
	if (world.hit(r, 0, infinity, record)) {
		return 0.5 * (record.normal + color(1, 1, 1));
	}
	vec3 unitDirection = normalize(r.direction());
	auto t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void writeColorToBuffer(const color color, int pixelNum, uint8_t* buffer) {
	rgbColor rgb = convertToRGB(color);
	int pixelPos = pixelNum * 3;
	buffer[pixelPos] = rgb.r;
	buffer[pixelPos + 1] = rgb.g;
	buffer[pixelPos + 2] = rgb.b;
}

void writeImageBufferToFile(const uint8_t *imageData, const int imageWidth, const int imageHeight) {
	stbi_write_jpg("./imageOut.jpg", imageWidth, imageHeight, 3, imageData, 100);
}