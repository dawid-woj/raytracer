#pragma once

#include <iostream>
#include <memory>

using namespace std;

class Vec {
public:
	float x, y, z;

	Vec(float v = 0.f) : x(v), y(v), z(v) {}
	Vec(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec(const Vec &other) : x(other.x), y(other.y), z(other.z) {}
	Vec(Vec&& other) : x(move(other.x)), y(move(other.y)),
		z(move(other.z)) {}

	Vec& operator=(const Vec &other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	Vec operator+(const Vec &other) const {
		return Vec(x + other.x, y + other.y, z + other.z);
	}
	Vec& operator+=(const Vec &other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec operator-(const Vec &other) const {
		return Vec(x - other.x, y - other.y, z - other.z);
	}
	Vec& operator-=(const Vec &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec operator-() const {
		return Vec(-x, -y, -z);
	}

	Vec operator*(float r) const {
		return Vec(x*r, y*r, z*r);
	}
	Vec& operator*=(float r) {
		x *= r;
		y *= r;
		z *= r;
		return *this;
	}

	Vec operator*(const Vec &other) const {
		return Vec(x*other.x, y*other.y, z*other.z);
	}
	Vec& operator*=(const Vec &other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	// dot product:
	float operator%(const Vec &other) const {
		return x*other.x + y*other.y + z*other.z;
	}

	// cross product:
	Vec operator^(const Vec &other) const {
		return Vec(y*other.z - z*other.y, z*other.x - x*other.z,
			x*other.y - y*other.x);
	}

	// normalizing:
	Vec operator!() const {
		return *this * (1 / sqrt(*this % *this));
	}
	Vec& normalize() {
		float mod = sqrt(*this % *this);
		x /= mod;
		y /= mod;
		z /= mod;
		return *this;
	}
};

ostream& operator<<(ostream &out, const Vec &vec) {
	return out << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}