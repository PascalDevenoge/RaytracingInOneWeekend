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
    rgb.r = static_cast<int>(256 * clamp(sqrt(color.x()), 0.0, 0.999));
    rgb.g = static_cast<int>(256 * clamp(sqrt(color.y()), 0.0, 0.999));
    rgb.b = static_cast<int>(256 * clamp(sqrt(color.z()), 0.0, 0.999));
    return rgb;
}

void writeColor(std::ostream& out, color color) {
    rgbColor rgb = convertToRGB(color);
    out << rgb.r << ' '
        << rgb.g << ' '
        << rgb.b << '\n';
}
