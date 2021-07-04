#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:

	double comp[3];

	vec3() : comp{ 0,0,0 } {};
	vec3(double x, double y, double z) : comp{ x,y,z } {};

	double x() const { return comp[0]; }
	double y() const { return comp[1]; }
	double z() const { return comp[2]; }

	vec3 operator-() const { return vec3(-comp[0], -comp[1], -comp[2]); }
	double operator[](int i) const { return comp[i]; }
	double& operator[](int i) { return comp[i]; }

	vec3& operator+=(const vec3& v) {
		comp[0] += v.comp[0];
		comp[1] += v.comp[1];
		comp[2] += v.comp[2];
		return *this;
	}

	vec3& operator-=(const vec3& v) {
		comp[0] -= v.comp[0];
		comp[1] -= v.comp[1];
		comp[2] -= v.comp[2];
		return *this;
	}

	vec3& operator*=(const double t) {
		comp[0] *= t;
		comp[1] *= t;
		comp[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t) {
		return *this *= 1 / t;
	}

	double length() const {
		return sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return comp[0] * comp[0] + comp[1] * comp[1] + comp[2] * comp[2];
	}

	vec3& normalize() {
		double length = this->length();
		comp[0] /= length;
		comp[1] /= length;
		comp[2] /= length;
		return *this;
	}
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3& v) {
	return out << v.comp[0] << ' ' << v.comp[1] << ' ' << v.comp[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.comp[0] + v.comp[0], u.comp[1] + v.comp[1], u.comp[2] + v.comp[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.comp[0] - v.comp[0],
		u.comp[1] - v.comp[1],
		u.comp[2] - v.comp[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.comp[0] * v.comp[0],
		u.comp[1] * v.comp[1],
		u.comp[2] * v.comp[2]);
}

inline vec3 operator*(const double t, const vec3& v) {
	return vec3(t * v.comp[0], t * v.comp[1], t * v.comp[2]);
}

inline vec3 operator*(const vec3& v, const double t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, const double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.comp[0] * v.comp[0]
		 + u.comp[1] * v.comp[1]
		 + u.comp[2] * v.comp[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.comp[1] * v.comp[2] - u.comp[2] * v.comp[1],
				u.comp[2] * v.comp[0] - u.comp[0] * v.comp[2],
				u.comp[0] * v.comp[1] - u.comp[1] * v.comp[0]);
}

inline vec3 normalize(const vec3 v) {
	return v / v.length();
}
