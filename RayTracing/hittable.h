#pragma once
#include "ray.h"
#include "material.h"

class material;
struct hit_record
{
	double t;
	point3 p;
	vec3 normal;
	bool frontFace;  // 区分外面内面
	std::shared_ptr<material> materialPtr;

	void set_face_normal(const ray& r, const vec3& outward_normal) {
		frontFace = r.getDirection().dot(outward_normal) < 0;
		if (frontFace) {
			normal = outward_normal;
		}
		else {
			normal = -outward_normal;
		}
	}
};


class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

