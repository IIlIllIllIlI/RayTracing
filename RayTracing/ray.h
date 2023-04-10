#pragma once
#include "vec3.h"

class ray
{
private:
	point3  _origin;
	vec3 _direction;
public:
	ray() {};
	ray(const vec3& origin, const vec3& direction) : _origin(origin), _direction(direction) {}

	point3 getOrigin() const { return _origin; }
	vec3 getDirection() const { return _direction; }
	point3 at(double t) const { return _origin + t * _direction; }
};

