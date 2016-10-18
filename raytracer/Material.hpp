#pragma once

#include "Vec.hpp"

class Material {
public:
	Vec ambient;
	Vec diffuse;
	Vec specular;
	float shininess; // > 0
	float reflectivity; //0..1
	float refractive_index; // > 1
	bool transparent;

	Material() : ambient(0.1f), diffuse(0.f), specular(0.9f), shininess(10.f),
		reflectivity(0.f), refractive_index(1.f), transparent(false) {}
	Material(const Vec &d) : ambient(0.1f), diffuse(d), specular(0.9f), shininess(10.f),
		reflectivity(0.f), refractive_index(1.f), transparent(false) {}
	Material(const Vec &d, const Vec &s, const Vec &a, float sh, float refl, float refr,
		bool transp) : ambient(a), diffuse(d), specular(s), shininess(sh),
		reflectivity(refl), refractive_index(refr), transparent(false) {}
	Material(const Material &other) : ambient(other.ambient),
		diffuse(other.diffuse), specular(other.specular),
		shininess(other.shininess), reflectivity(other.reflectivity),
		refractive_index(other.refractive_index), transparent(other.transparent) {}
	Material(Material&& other) : ambient(move(other.ambient)), diffuse(move(other.diffuse)),
		specular(move(other.specular)), shininess(move(other.shininess)),
		reflectivity(move(other.reflectivity)), refractive_index(move(other.refractive_index)),
		transparent(move(other.transparent)) {}
};