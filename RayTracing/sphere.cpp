#include "sphere.h"

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	// A -> ray_origin
	// B -> ray_direction
	// C -> sphere center

	// t^2 * B.dot(B) + 2t * B.dot(A - C) + (A - C).dot(A - C) - R^2 = 0

	vec3 oc = r.getOrigin() - _center;  // A - C
	double a = r.getDirection().dot(r.getDirection());
	double b = 2.0 * r.getDirection().dot(oc);
	double c = oc.dot(oc) - _radius * _radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant > 0) {
		double tmp = (-b - sqrt(discriminant)) / (2.0 * a);
		if (tmp < t_max && tmp > t_min) {
			rec.t = tmp;
			rec.p = r.at(tmp);
			vec3 outward_normal = (rec.p - _center).normalize();
			rec.set_face_normal(r, outward_normal);
			rec.materialPtr = _materialPtr;

			return true;
		}
		tmp = (-b + sqrt(discriminant)) / (2.0 * a);
		if (tmp < t_max && tmp > t_min) {
			rec.t = tmp;
			rec.p = r.at(tmp);
			vec3 outward_normal = (rec.p - _center).normalize();
			rec.set_face_normal(r, outward_normal);
			rec.materialPtr = _materialPtr;

			return true;
		}
	}
	return false;
}
