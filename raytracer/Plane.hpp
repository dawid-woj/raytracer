#pragma once

#include "Object.hpp"

class Plane : public Object {
public:
	Vec normal;

	Plane(const Vec &pos, const Material &m, const Vec &n)
		: Object(pos, m), normal(n) {}
	Plane(const Plane &other) : Object(other),
		normal(other.normal) {}
	Plane(Plane&& other) : Object(move(other)),
		normal(move(other.normal)) {}

	virtual bool intersect(const Ray &ray, float &t0, float &t1) const {
		float dn = ray.dir % normal;
		if (dn < 0.0001f)
			return false;
		float t = ((pos - ray.origin) % normal) / dn;
		t0 = t; t1 = t;
		return (t >= 0.0001f);
	}

	virtual Vec getNormal(const Vec &intersection) const {
		return normal;
	}
};