#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

void writeImageBufferToFile(uint8_t* imageData);

int main() {

	uint8_t* image_data = new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * 3];

	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		for (int j = 0; j < IMAGE_WIDTH; j++) {
			auto r = double(i) / (IMAGE_WIDTH - 1);
			auto g = double(j) / (IMAGE_HEIGHT - 1);
			auto b = 0.25;

			uint8_t ir = static_cast<uint8_t> (255.999 * r);
			uint8_t ig = static_cast<uint8_t> (255.999 * g);
			uint8_t ib = static_cast<uint8_t> (255.999 * b);

			int pixelPos = (i * IMAGE_WIDTH + j) * 3;

			image_data[pixelPos] = ir;
			image_data[pixelPos + 1] = ig;
			image_data[pixelPos + 2] = ib;
		}
	}

	writeImageBufferToFile(image_data);
	delete[] image_data;
}

void writeImageBufferToFile(uint8_t *imageData) {
	stbi_write_jpg("./imageOut.jpg", IMAGE_WIDTH, IMAGE_HEIGHT, 3, imageData, 100);
}