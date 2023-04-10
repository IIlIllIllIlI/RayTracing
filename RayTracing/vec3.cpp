#include "vec3.h"


vec3 vec3::random()
{
    util util;
    return vec3(util.randomDouble(), util.randomDouble(), util.randomDouble());
}

vec3 vec3::random(double min, double max)
{
    util util;
    return vec3(util.randomDouble(min, max), util.randomDouble(min, max), util.randomDouble(min, max));
}

vec3 vec3::randomInUnitSphere()
{
    while (true) {
        vec3 p = vec3::random(-1, 1);
        if (p.squaredLength() >= 1) continue;
        return p;
    }
}

vec3 vec3::randomUnitVector()
{
    return randomInUnitSphere().normalize();
}

vec3& vec3::operator+=(const vec3& v2)
{
    value[0] += v2.value[0];
    value[1] += v2.value[1];
    value[2] += v2.value[2];
    return *this;
}

vec3& vec3::operator-=(const vec3& v2)
{
    value[0] -= v2.value[0];
    value[1] -= v2.value[1];
    value[2] -= v2.value[2];
    return *this;
}

double vec3::dot(const vec3& v2) const
{
    return value[0] * v2.value[0] + value[1] * v2.value[1] + value[2] * v2.value[2];
}

vec3 vec3::cross(const vec3& v2) const
{
    return vec3(
        value[1] * v2.value[2] - value[2] * v2.value[1],
        value[2] * v2.value[0] - value[0] * v2.value[2],
        value[0] * v2.value[1] - value[1] * v2.value[0]
    );
}

vec3& vec3::operator*=(const double s)
{
    value[0] *= s;
    value[1] *= s;
    value[2] *= s;
    return *this;
}

vec3& vec3::operator/=(const double s)
{
    return *this *= 1 / s;
}

std::ostream& vec3::operator<<(std::ostream& cout)
{
    return cout << value[0] << ' ' << value[1] << ' ' << value[2];
}

double vec3::length() const
{
    return sqrt(squaredLength());
}

double vec3::squaredLength() const
{
    return value[0] * value[0] + value[1] * value[1] + value[2] * value[2];
}

vec3 vec3::normalize() const
{
    double length = this->length();
    return vec3(value[0] / length, value[1] / length, value[2] / length);
}

vec3 vec3::reflect(const vec3& normal) const
{
    vec3 tmp(value[0], value[1], value[2]);
    return vec3(tmp - 2 * (tmp.dot(normal)) * normal);
}

vec3 vec3::refract(const vec3& normal, double refractionIndexRatio) const
{
    double cosTheta = fmin((-*this).dot(normal), 1.0);
    vec3 rOutPerp = refractionIndexRatio * (*this + cosTheta * normal);
    vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.squaredLength())) * normal;
    return rOutPerp + rOutParallel;
}

bool vec3::lengthNearZero() const
{
    const auto s = 1e-8;
    return (fabs(value[0]) < s) && (fabs(value[1]) < s) && (fabs(value[2]) < s);
}

vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(
        v1.value[0] + v2.value[0],
        v1.value[1] + v2.value[1],
        v1.value[2] + v2.value[2]
    );
}

vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(
        v1.value[0] - v2.value[0],
        v1.value[1] - v2.value[1],
        v1.value[2] - v2.value[2]
    );
}

vec3 operator*(const double t, const vec3& v)
{
    return vec3(
        v.value[0] * t,
        v.value[1] * t,
        v.value[2] * t
    );
}

vec3 operator*(const vec3& v, const double t)
{
    return vec3(
        v.value[0] * t,
        v.value[1] * t,
        v.value[2] * t
    );
}

vec3 operator/(const vec3& v, const double t)
{
    return vec3(
        v.value[0] / t,
        v.value[1] / t,
        v.value[2] / t
    );
}
