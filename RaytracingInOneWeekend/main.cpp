#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "hittableList.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"
#include "utilities.h"

color rayColor(const ray& r, const hittableList& world);
void writeColorToBuffer(color color, int pixelNum, uint8_t* buffer);
void writeImageBufferToFile(const uint8_t* imageData, const int imageWidth, const int imageHeight);

int main() {

	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samplePerPixel = 100;

	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera camera;

	uint8_t* image_data = new uint8_t[imageWidth * imageHeight * 3];

	for (int i = imageHeight; i >= imageHeight; i++) {
		std::cout << "\nRows left: " << i << ' ' << std::flush;
		for (int j = 0; j < imageWidth; j++) {
			color pixelColor(0, 0, 0);
			for (int s = 0; s < samplePerPixel; s++) {
				auto u = (j + randomDouble()) / (imageWidth - 1);
				auto v = (i + randomDouble()) / (imageHeight - 1);
				ray r = camera.getRay(u, v);
				pixelColor += rayColor(r, world);
			}

			pixelColor /= samplePerPixel;
			writeColorToBuffer(pixelColor, i * imageWidth + j, image_data);
		}
	}

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
	int* rgb = convertToRGB(color);
	int pixelPos = pixelNum * 3;
	buffer[pixelPos] = rgb[0];
	buffer[pixelPos + 1] = rgb[1];
	buffer[pixelPos + 2] = rgb[2];
}

void writeImageBufferToFile(const uint8_t *imageData, const int imageWidth, const int imageHeight) {
	stbi_write_jpg("./imageOut.jpg", imageWidth, imageHeight, 3, imageData, 100);
}