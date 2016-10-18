#pragma once

#include <opencv2/core.hpp>

#include "Object.hpp"
#include "Scene.hpp"

#define MAX_DEPTH 3


class Renderer {
public:
	Renderer() {}

	cv::Mat render(const Scene &scene, const Camera &camera) {
		cv::Mat image = cv::Mat(camera.getHeight(), camera.getWidth(),
			CV_8UC3, cv::Scalar(0, 0, 0));
		int rows = image.rows;
		int cols = image.cols;
		uchar* p;
		for (int i = 0; i < rows; ++i) {
			p = image.ptr<uchar>(i);
			for (int j = 0; j < cols; ++j) {
				float pix_x = (2 * ((j + 0.5f) * camera.getInvWidth()) - 1)
					* camera.getAngle() * camera.getAspectRatio();
				float pix_y = (1 - 2 * ((i + 0.5f) * camera.getInvHeight()))
					* camera.getAngle();
				float pix_z = -1.f;
				Vec pix = Vec(pix_x, pix_y, pix_z);
				Vec ray_dir = !(pix - camera.pos);
				Vec pixcolor = castRay(scene, camera, Ray(camera.pos, ray_dir), 0);
				// BGR:
				p[j * 3] = (unsigned char)(min(1.f, pixcolor.z) * 255);
				p[j * 3 + 1] = (unsigned char)(min(1.f, pixcolor.y) * 255);
				p[j * 3 + 2] = (unsigned char)(min(1.f, pixcolor.x) * 255);
			}
		}
		return image;
	}

private:

	// returns RGB
	Vec castRay(const Scene &scene, const Camera &camera, const Ray &ray,
		unsigned int depth)
	{
		Vec color = Vec(0.f);
		float t;

		Object *closest = scene.intersect(ray, t);
		if (!closest)
			return color;

		// L - vector towards light
		// V - vector towards camera
		// R - vector of reflected ray 
		// R_l - vector of reflected light towards camera

		Vec intersection = ray.origin + (ray.dir * t);
		Vec N = closest->getNormal(intersection);
		Vec V = !(camera.pos - intersection);

		color += calculateAmbientDiffuseSpecular(scene, closest, intersection, V, N);

		return color;
	}

	Vec calculateAmbientDiffuseSpecular(const Scene &scene, Object *obj,
		const Vec &intersection, const Vec &V, const Vec &N)
	{
		bool inAnyShadow = isInAnyShadow(scene, intersection, N);
		Vec color = obj->mat.ambient * scene.ambient; // global ambient component
		for (Light light : scene.lights) {
			Vec _L = light.pos - intersection;
			Vec L = !_L;

			float lamb = L % N;
			if (lamb < 0.001f) // light's behind object
				continue;

			Ray shadow_ray = Ray(intersection, L);
			float light_distance = _L % _L;
			if (isInShadow(scene, shadow_ray, light_distance))
				continue;

			float sf = 0.f;
			float sp_coef = 0.f;
			if (!inAnyShadow) {
				Vec R_l = !(N * 2 * lamb - L);
				sf = R_l % V;
				sp_coef = 0.f;
				if (sf > 0.001f)
					sp_coef = pow(sf, obj->mat.shininess);
			}

			float ld_coef = 1.f / light_distance;
			if (ld_coef < 0.001f)
				ld_coef = 0.f;

			Vec diffuse = obj->mat.diffuse * light.diffuse * lamb * light.intensity * ld_coef;
			Vec specular = obj->mat.specular * light.specular * sp_coef * light.intensity * ld_coef;
			color += diffuse + specular;
		}
		return color;
	}

	bool isInAnyShadow(const Scene &scene, const Vec &point,
		const Vec &normal)
	{
		for (Light light : scene.lights) {
			Vec _L = light.pos - point;
			Vec L = !_L;
			float lamb = L % normal;
			if (lamb < 0.001f) // light's behind object
				continue;
			Ray shadow_ray = Ray(point, L);
			float light_distance = _L % _L;
			if (isInShadow(scene, shadow_ray, light_distance))
				return true;
		}
		return false;
	}

	bool isInShadow(const Scene &scene, const Ray &shadow_ray,
		float light_distance)
	{
		float t;
		Object *closest = scene.intersect(shadow_ray, t);
		if (closest) {
			Vec h = shadow_ray.origin + (shadow_ray.dir * t);
			float obj_distance = h % h;
			if (light_distance > obj_distance)
				return true;
		}
		return false;
	}
};