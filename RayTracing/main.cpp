#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "util.h"
#include "material.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

// image
const double ASPECT_RATIO = 16.0 / 9.0;
const int IMAGE_WIDTH = 400;
const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
const int SAMPLE_PER_PIXEL = 100;
const int SAMPLE_MAX_DEPTH = 50;

void makePPM(int width, int height, std::vector<color> data)
{
	std::ofstream ofs;
	ofs.open("RayTracing.ppm", std::ios::out);
	// P3 -> ASCII format   nx->column   ny->row   255->maxColor
	ofs << "P3\n" << width << " " << height << "\n255\n";
	for (int i = 0; i < data.size(); i++)
	{
		color pixelColor = data[i];
		writeColor(ofs, pixelColor, SAMPLE_PER_PIXEL);
	}
	ofs.close();
	std::cout << "output succeed" << std::endl;
}

vec3 rayColor(const ray& r, hittable& world, int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0) {
		return color(0, 0, 0);
	}

	hit_record rec;
	util util;

	if (world.hit(r, 0.001, util.DOUBLE_INFINITY, rec)) {
		ray scattered;
		color attenuation;
		if (rec.materialPtr->scatter(r, rec, attenuation, scattered)) {
			vec3 tmp = rayColor(scattered, world, depth - 1);

			return vec3(attenuation.x() * tmp.x(), 
				attenuation.y() * tmp.y(), attenuation.z() * tmp.z());
		}
		return color(0, 0, 0);
	}
	vec3 unitDirection = r.getDirection().normalize();
	double t = 0.5f * (unitDirection.y() + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}


int main()
{
	// camera
	camera cam;

	// Objects
	hittable_list world;

	auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = std::make_shared<dielectric>(1.5);
	auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

	world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));


	//hittable_list objects;
	//objects.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	//objects.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Render
	std::vector<color> data;
	util util;
	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			color pixelColor(0, 0, 0);
			for (int s = 0; s < SAMPLE_PER_PIXEL; s++) {
				auto u = (i + util.randomDouble()) / (IMAGE_WIDTH - 1);
				auto v = (j + util.randomDouble()) / (IMAGE_HEIGHT - 1);
				ray r = cam.getRay(u, v);
				pixelColor += rayColor(r, world, SAMPLE_MAX_DEPTH);
			}
			data.push_back(pixelColor);
		}
	}
	std::cerr << "\nDone.\n";
	makePPM(IMAGE_WIDTH, IMAGE_HEIGHT, data);
}


