#pragma once

#include <cmath>

#include "Vec.hpp"

#define PI 3.141592653589793f

class Camera {
public:
	Vec pos;
private:
	float fov; // field of view, degrees
	int w, h;
	float inv_w, inv_h;
	float angle;
	float aspect_ratio;

public:

	Camera(const Vec &p, float fov, int w, int h)
		: pos(p), fov(fov), w(w), h(h)
	{
		inv_w = 1.f / w;
		inv_h = 1.f / h;
		aspect_ratio = w / float(h);
		angle = tan(PI * 0.5f * fov / 180.f);
	}

	void setFov(float f) {
		fov = f;
		angle = tan(PI * 0.5f * f / 180.f);
	}
	void setWidth(int wi) {
		w = wi;
		inv_w = 1.f / wi;
		aspect_ratio = wi / float(h);
	}
	void setHeight(int he) {
		h = he;
		inv_h = 1.f / he;
		aspect_ratio = w / float(he);
	}
	void setSize(int wi, int he) {
		w = wi; h = he;
		inv_w = 1.f / wi;
		inv_h = 1.f / he;
		aspect_ratio = wi / float(he);
	}

	float getFov() const {
		return fov;
	}
	int getWidth() const {
		return w;
	}
	int getHeight() const {
		return h;
	}
	float getInvWidth() const {
		return inv_w;
	}
	float getInvHeight() const {
		return inv_h;
	}
	float getAngle() const {
		return angle;
	}
	float getAspectRatio() const {
		return aspect_ratio;
	}
};