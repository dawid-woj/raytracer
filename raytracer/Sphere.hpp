#pragma once

#include "Object.hpp"

class Sphere : public Object {
public:
	float r, r2;

	Sphere() : Object(), r(1.f), r2(1.f) {}
	Sphere(const Vec &p, const Material &m, float r)
		: Object(p, m), r(r), r2(r*r) {}
	Sphere(const Sphere &other)
		: Object(other), r(other.r), r2(other.r2) {}
	Sphere(Sphere&& other) : Object(move(other)), r(move(other.r)),
		r2(move(other.r2)) {}

	virtual bool intersect(const Ray &ray, float &t0, float &t1) const {
		Vec l = pos - ray.origin;
		float ts = l % ray.dir;
		if (ts < 0.001f)
			return false;
		float h = sqrt(l%l - ts*ts);
		if (h > r)
			return false;
		float tas = sqrt(h*h + r2);
		t0 = ts - tas;
		t1 = ts + tas;
		return true;
	}

	virtual Vec getNormal(const Vec &intersection) const {
		Vec normal = !(intersection - pos);
		return normal;
	}
};