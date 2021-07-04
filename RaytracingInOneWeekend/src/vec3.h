#pragma once

#include <cmath>
#include <iostream>

#include "utilities.h"

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

	bool nearZero() const {
		const auto s = 1e-8;
		return (fabs(comp[0]) < s && (fabs(comp[1]) < s) && fabs(comp[2]) < s);
	}

	static vec3 normalize(const vec3& v);
	static vec3 random();
	static vec3 random(double min, double max);
	static vec3 randomInUnitSphere();
	static vec3 randomUnitVector();
	static vec3 randomInHemisphere(const vec3& normal);
	static vec3 randomInUnitDisk();
	static vec3 reflect(const vec3& v, const vec3& normal);
	static vec3 refract(const vec3& uv, const vec3& normal, double etaIOverEtaT);
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

inline vec3 vec3::normalize(const vec3& v) {
	return v / v.length();
}

inline vec3 vec3::random() {
	return vec3(randomDouble(), randomDouble(), randomDouble());
}

inline vec3 vec3::random(double min, double max) {
	return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline vec3 vec3::randomInUnitSphere() {
	vec3 vector;
	do {
		vector = vec3::random(-1, 1);
	} while (vector.lengthSquared() >= 1);
	return vector;
}

inline vec3 vec3::randomUnitVector() {
	return vec3::normalize(randomInUnitSphere());
}

inline vec3 vec3::randomInHemisphere(const vec3& normal) {
	vec3 inUnitSphere = randomInUnitSphere();
	return (dot(inUnitSphere, normal) > 0.0) ? inUnitSphere : -inUnitSphere;
}

inline vec3 vec3::randomInUnitDisk() {
	vec3 p;
	do {
		p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
	} while (p.lengthSquared() >= 1);
	return p;
}

inline vec3 vec3::reflect(const vec3& v, const vec3& normal) {
	return v - 2 * dot(v, normal) * normal;
}

inline vec3 vec3::refract(const vec3& uv, const vec3& normal, double etaIOverEtaT) {
	auto cosTheta = fmin(dot(-uv, normal), 1.0);
	vec3 rOutPrep = etaIOverEtaT * (uv + cosTheta * normal);
	vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPrep.lengthSquared())) * normal;
	return rOutPrep + rOutParallel;
}
