#pragma once

#include <iostream>

#include "vec.h"

int* convertToRGB(color color) {
    int rgb[3];
    rgb[0] = static_cast<int>(255.999 * color.x());
    rgb[1] = static_cast<int>(255.999 * color.y());
    rgb[2] = static_cast<int>(255.999 * color.z());
    return rgb;
}

void writeColor(std::ostream& out, color color) {
    int* rgb = convertToRGB(color);
    out << rgb[0] << ' '
        << rgb[1] << ' '
        << rgb[2] << '\n';
}