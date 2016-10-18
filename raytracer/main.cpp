#include <iostream>
#include <memory>
#include <cmath>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Vec.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

using namespace std;


int main()
{
	Scene scene = Scene();
	
	unique_ptr<Sphere> s1(new Sphere(Vec(2.f, 0.f, -17.f), Material(Vec(0.9f, 0.f, 0.f)), 3.f)); //red
	unique_ptr<Sphere> s2(new Sphere(Vec(-2.f, -1.f, -27.f), Material(Vec(0.f, 0.9f, 0.f)), 4.f)); //green
	unique_ptr<Sphere> s3(new Sphere(Vec(-2.f, 2.f, -20.5f), Material(Vec(0.f, 0.0f, 0.9f)), 0.5f)); //blue
	scene.objects.push_back(move(s1));
	scene.objects.push_back(move(s2));
	scene.objects.push_back(move(s3));

	//unique_ptr<Plane> p(new Plane(Vec(0.f, -7.f, -10.f), Material(Vec(0.9f, 0.0f, 0.f)), !Vec(0.f, 1.f, 0.2f)));
	//scene.objects.push_back(move(p));

	Light l1 = Light(Vec(-10.f, 10.f, 0.f), 350.f, Vec(0.8f), Vec(0.8f));
	Light l2 = Light(Vec(11.f, 7.5f, -5.f), 120.f, Vec(0.9f), Vec(0.7f));
	scene.lights.push_back(l1);
	scene.lights.push_back(l2);

	Camera camera = Camera(Vec(0.f), 40, 600, 400);
	scene.cameras.push_back(camera);

	Renderer rend = Renderer();
	cv::Mat image = rend.render(scene, camera);

	cv::namedWindow("Raytracer", cv::WINDOW_AUTOSIZE);
	cv::imshow("Raytracer", image);
	cv::waitKey(0);

	return 0;
}