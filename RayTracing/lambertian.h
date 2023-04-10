#pragma once
#include "material.h"
#include "vec3.h"

class lambertian : public material {
public:
    color _albedo;

    lambertian(const color& a) : _albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, 
         color& attenuation, ray& scattered) const override;


};

