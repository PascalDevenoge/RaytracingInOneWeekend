#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "color.h"
#include "vec.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

void writeImageBufferToFile(uint8_t* imageData);

int main() {

	uint8_t* image_data = new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * 3];

	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		std::cout << "\nRows left: " << i << ' ' << std::flush;
		for (int j = 0; j < IMAGE_WIDTH; j++) {
			color color(double(i) / (IMAGE_WIDTH - 1), double(j) / (IMAGE_HEIGHT - 1), 0.25);
			int* rgb = convertToRGB(color);

			int pixelPos = (i * IMAGE_WIDTH + j) * 3;

			image_data[pixelPos] = rgb[0];
			image_data[pixelPos + 1] = rgb[1];
			image_data[pixelPos + 2] = rgb[2];
		}
	}

	writeImageBufferToFile(image_data);
	delete[] image_data;
	std::cout << "\nFinished";
}

void writeImageBufferToFile(uint8_t *imageData) {
	stbi_write_jpg("./imageOut.jpg", IMAGE_WIDTH, IMAGE_HEIGHT, 3, imageData, 100);
}