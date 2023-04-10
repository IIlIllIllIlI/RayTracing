#pragma once
#include <iostream>
#include "util.h"

class vec3
{
	friend vec3 operator+(const vec3& v1, const vec3& v2);
	friend vec3 operator-(const vec3& v1, const vec3& v2);

	friend vec3 operator*(const double t, const vec3& v);
	friend vec3 operator*(const vec3& v, const double t);
	friend vec3 operator/(const vec3& v, const double t);

private:
	double value[3];

public:
	vec3() : value{ 0, 0, 0 } {}
	vec3(double v1, double v2, double v3) : value{v1, v2, v3} {}
	static vec3 random();
	static vec3 random(double min, double max);
	static vec3 randomInUnitSphere();
	static vec3 randomUnitVector();

	inline double x() const { return value[0]; }
	inline double y() const { return value[1]; }
	inline double z() const { return value[2]; }
	
	inline vec3 operator-() const { return vec3(-value[0], -value[1], -value[2]); }

	// 返回引用，因此允许 vec[1] = 2 赋值
	inline double& operator[](int i) { return value[i]; }

	vec3& operator+=(const vec3& v2);
	vec3& operator-=(const vec3& v2);
	double dot(const vec3& v2) const;
	vec3 cross(const vec3& v2) const;

	vec3& operator*=(const double s);
	vec3& operator/=(const double s);
	std::ostream& operator<<(std::ostream& out);

	double length() const;
	double squaredLength() const;
	vec3 normalize() const;

	// assume normal has unit length
	vec3 reflect(const vec3& normal) const;

	//
	vec3 refract(const vec3& normal, double refractionIndexRatio) const;

	// Return true if the vector is close to zero in all dimensions.
	bool lengthNearZero() const;
};

vec3 operator+(const vec3& v1, const vec3& v2);
vec3 operator-(const vec3& v1, const vec3& v2);

vec3 operator*(const double t, const vec3& v);
vec3 operator*(const vec3& v, const double t);
vec3 operator/(const vec3& v, const double t);

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color