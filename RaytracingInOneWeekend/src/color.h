#pragma once

#include <iostream>
#include <vector>

#include "vec3.h"

struct rgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

rgbColor convertToRGB(color color) {
    rgbColor rgb;
    rgb.r = static_cast<int>(255.999 * color.x());
    rgb.g = static_cast<int>(255.999 * color.y());
    rgb.b = static_cast<int>(255.999 * color.z());
    return rgb;
}

void writeColor(std::ostream& out, color color) {
    rgbColor rgb = convertToRGB(color);
    out << rgb.r << ' '
        << rgb.g << ' '
        << rgb.b << '\n';
}
