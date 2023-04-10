#pragma once
#include "material.h"


class dielectric : public material {
public:
    double ir; // Index of Refraction

    dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

    virtual bool scatter(const ray& rayIn, const hit_record& rec, 
        color& attenuation, ray& scattered) const override;
private:
    static double reflectance(double cosine, double ref_idx);

};

