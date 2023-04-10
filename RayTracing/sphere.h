#pragma once
#include "hittable.h"
#include <memory>

class sphere : public hittable
{
public:
	point3 _center;
	double _radius;
	std::shared_ptr<material> _materialPtr;

	sphere() { _radius = 1; }
	sphere(point3 center, double r, std::shared_ptr<material> materialPtr)
		: _center(center), _radius(r), _materialPtr(materialPtr) {};


	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

