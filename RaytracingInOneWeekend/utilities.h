#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

#include "ray.h"
#include "vec3.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees) {
	return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	else if (x > max) return max;
	else return x;
}

inline double randomDouble() { return rand() / (RAND_MAX + 1.0); }

inline double randomDouble(double min, double max) { return min + (max - min) * randomDouble(); }

inline double randomDoubleStd() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}
