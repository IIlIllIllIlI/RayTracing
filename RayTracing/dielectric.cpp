#include "dielectric.h"

bool dielectric::scatter(const ray& rayIn, const hit_record& rec, color& attenuation, ray& scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    double refractionRatio = rec.frontFace ? (1.0 / ir) : ir;

    vec3 unitDirection = rayIn.getDirection().normalize();
    //double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    //double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    double cosTheta = fmin(-unitDirection.dot(rec.normal), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    vec3 direction;
    util util;
    if (cannotRefract || reflectance(cosTheta, refractionRatio) > util.randomDouble()) {
        // Total Internal Reflection
        direction = unitDirection.reflect(rec.normal);
    }
    else {
        direction = unitDirection.refract(rec.normal, refractionRatio);
    }

    scattered = ray(rec.p, direction);
    return true;
}

double dielectric::reflectance(double cosine, double ref_idx)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
