#pragma once

#include "Vec.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Object {
public:
	Vec pos;
	Material mat;

	Object() : pos(), mat() {}
	Object(const Vec &p, const Material &m) : pos(p), mat(m) {}
	Object(const Object &other)
		: pos(other.pos), mat(other.mat) {}
	Object(Object&& other) : pos(move(other.pos)),
		mat(move(other.mat)) {}
	virtual ~Object() {};

	virtual bool intersect(const Ray &ray, float &t0,
		float &t1) const = 0;
	virtual Vec getNormal(const Vec &intersection) const = 0;
};