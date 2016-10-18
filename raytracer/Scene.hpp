#pragma once

#include <vector>

#include "Camera.hpp"

using namespace std;


class Scene {
public:
	vector<Camera> cameras;

	vector<unique_ptr<Object> > objects;
	vector<Light> lights;

	Vec ambient;
	float refractive_index;

	Scene() : ambient(0.1f), refractive_index(1.f) {}
	Scene(const Vec &a, float n) : ambient(n),
		refractive_index(n) {}

	// intersection, t - output parameters:
	Object* intersect(const Ray &ray, float &t) const {
		t = INFINITY;
		Object *closest = NULL;
		for (auto const& _obj : objects) {
			Object &obj = *_obj;
			float t0 = INFINITY, t1 = INFINITY;
			if (obj.intersect(ray, t0, t1)) {
				if (t0 < 0.001f)
					t0 = t1;
				if (t0 > 0.001f && t0 < t) {
					t = t0;
					closest = &obj;
				}
			}
		}
		return closest;
	}
};