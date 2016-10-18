#pragma once

#include "Vec.hpp"

class Light {
public:
	Vec pos;
	float intensity;
	Vec diffuse;
	Vec specular;

	Light(const Vec &p) : pos(p), intensity(200.f), diffuse(0.9f), specular(0.9f) {}
	Light(const Vec &p, float i, const Vec &d, const Vec &s)
		: pos(p), intensity(i), diffuse(d), specular(s) {}
	Light(const Light &other) : pos(other.pos),
		intensity(other.intensity), diffuse(other.diffuse),
		specular(other.specular) {}
	Light(Light&& other) : pos(move(other.pos)), intensity(move(other.intensity)),
		diffuse(move(other.diffuse)), specular(move(other.specular)) {}
};
