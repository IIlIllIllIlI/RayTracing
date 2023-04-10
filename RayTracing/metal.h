#pragma once
#include "vec3.h"
#include "material.h"
class metal : public material
{
public:
    color _albedo;
    double _fuzz;

    metal(const color& a, double fuzz) : _albedo(a), _fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;
    
};

