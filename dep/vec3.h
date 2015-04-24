#pragma once
#ifndef _VEC3_CMATH_UTILS_H_
#define _VEC3_CMATH_UTILS_H_
#include <cmath>
#include "vec2.h"
struct vec3
{
	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };
		float v[3];
	};
	vec3() {}
	vec3(float x, float y, float z) :x(x), y(y), z(z) {}
	static vec3 zero() { return vec3(0, 0, 0); }
};


const vec3 operator-(const vec3 &v);
const float lengthSqr(const vec3 &v);
const float length(const vec3 &v);
const vec3 normal(const vec3 &v);

const float distanceSqr(const vec3 &l, const vec3 &r);
const float distance(const vec3 &l, const vec3 &r);
const float angleBetween(const vec3 &l, const vec3 &r);
const float dot(const vec3 &l, const vec3 &r);

const vec3 cross(const vec3 &l, const vec3 &r);
const vec3 operator+(const vec3 &l, const vec3 &r);
const vec3 operator-(const vec3 &l, const vec3 &r);
const vec3 operator/(const vec3 &l, float r);
const vec3 operator*(const vec3 &l, float r);
const vec3 operator/(float l, vec3 &r);
const vec3 operator*(float l, vec3 &r);

vec3 &operator+=(vec3 &l, const vec3 &r);
vec3 &operator-=(vec3 &l, const vec3 &r);
vec3 &operator/=(vec3 &l, float r);
vec3 &operator*=(vec3 &l, float r);

const bool operator==(const vec3 &l, const vec3 &r);
const bool operator!=(const vec3 &l, const vec3 &r);
const bool operator>=(const vec3 &l, const vec3 &r);
const bool operator<=(const vec3 &l, const vec3 &r);
const bool operator>(const vec3 &l, const vec3 &r);
const bool operator<(const vec3 &l, const vec3 &r);

#endif