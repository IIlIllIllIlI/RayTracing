#include "hittable_list.h"

bool hittable_list::hit(const ray& r, double tmin, double tmax, hit_record& rec) const
{
    hit_record tmpRec;
    bool hitAnything = false;
    double clostestSoFar = tmax;

    for (const std::shared_ptr<hittable>& object : objects) {
        if (object->hit(r, tmin, clostestSoFar, tmpRec)) {
            hitAnything = true;
            clostestSoFar = tmpRec.t;
            rec = tmpRec;
        }
    }
    return hitAnything;
}
