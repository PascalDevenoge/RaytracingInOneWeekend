#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

#include "hittableList.h"
#include "color.h"
#include "primitive/sphere.h"
#include "primitive/movingSphere.h"
#include "camera/basicCamera.h"
#include "camera/randomSupersamplingCamera.h"
#include "camera/depthOfFieldCamera.h"
#include "camera/motionBlurDOFCamera.h"
#include "utilities.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "bvhNode.h"
#include "texture/checkerTexture.h"

color rayColor(const ray& r, const hittable& world, int depth);
void writeColorToBuffer(color color, int pixelNum, uint8_t* buffer);
void writeImageBufferToFile(const uint8_t* imageData, const int imageWidth, const int imageHeight);
bvhNode randomScene();

int main() {

	// Image parameters
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 1200;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const double focalLength = 1.0;
	const int samplePerPixel = 500;
	const int maxDepth = 50;

	// Scene description
	auto world = randomScene();

	// Camera setup
	point3 position(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	motionBlurDOFCamera camera(position, lookat, vup, 20, aspectRatio, aperture, dist_to_focus, samplePerPixel, 0.0, 1.0);

	// Pixel buffer
	uint8_t* image_data = new uint8_t[imageWidth * imageHeight * 3];

	// Render loop
	for (int row = 0; row < imageHeight; row++) {
		std::cout << "\nRows left: " << imageHeight - row << ' ' << std::flush;

		for (int collumn = 0; collumn < imageWidth; collumn++) {
			color pixelColor(0, 0, 0);
			std::vector<ray> sampleRays = camera.getRaysForPixel((double) collumn / imageWidth, (double) row / imageHeight);
			for (const auto& sample : sampleRays) {
				pixelColor += rayColor(sample, world, maxDepth);
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

color rayColor(const ray& r, const hittable& world, int depth) {
	if (depth <= 0) {
		return color(0, 0, 0);
	}

	hitRecord record;
	if (world.hit(r, 0.001, infinity, record)) {
		ray scattered;
		color attenuation;
		if (record.material->scatter(r, record, attenuation, scattered)) {
			return attenuation * rayColor(scattered, world, depth - 1);
		}
		return color(0, 0, 0);
	}

	vec3 unitDirection = vec3::normalize(r.direction());
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

bvhNode randomScene() {
	hittableList world;

	auto checker = make_shared<checkerTexture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

	auto groundMaterial = make_shared<lambertian>(checker);
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto chooseMaterial = randomDouble();
			point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<abstractMaterial> sphereMaterial;

				if (chooseMaterial < 0.8) {
					// Diffuse
					auto albedo = color::random() * color::random();
					sphereMaterial = make_shared<lambertian>(albedo);
					auto center2 = center + vec3(0, randomDouble(0, 0.5), 0);
					world.add(make_shared<movingSphere>(center, center2, 0.0, 1.0, 0.2, sphereMaterial));
				} else if (chooseMaterial < 0.95) {
					// Metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = randomDouble(0, 0.5);
					sphereMaterial = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
				} else {
					// Glass
					sphereMaterial = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return bvhNode(world, 0.0, 1.0);
}