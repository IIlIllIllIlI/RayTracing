#include "metal.h"

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 reflectedDirection = r_in.getDirection().normalize().reflect(rec.normal);
    scattered = ray(rec.p, reflectedDirection + _fuzz * vec3::randomInUnitSphere());
    attenuation = _albedo;
    return scattered.getDirection().dot(rec.normal) > 0;
}
