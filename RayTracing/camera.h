#pragma once
#include "util.h"
#include "vec3.h"
#include "ray.h"

class camera
{
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

public:
    camera();

    ray getRay(double u, double v) const;
};

