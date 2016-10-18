#pragma once

#include "Vec.hpp"

class Ray {
public:
	Vec origin;
	Vec dir; //normalized

	Ray(const Vec &o, const Vec &d) : origin(o), dir(d) {}
	Ray(const Ray &other) : origin(other.origin), dir(other.dir) {}
	Ray(Ray&& other) : origin(move(other.origin)), dir(move(other.dir)) {}
};
