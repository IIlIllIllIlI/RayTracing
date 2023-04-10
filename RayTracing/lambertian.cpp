#include "lambertian.h"

bool lambertian::scatter(const ray& r_in, const hit_record& rec, 
    color& attenuation, ray& scattered) const
{
    vec3 scatterDirection = rec.normal + vec3::randomUnitVector();

    // Catch degenerate scatter direction
    if (scatterDirection.lengthNearZero())
        scatterDirection = rec.normal;

    scattered = ray(rec.p, scatterDirection);
    attenuation = _albedo;
    return true;
}
