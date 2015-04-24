#pragma once
#ifndef _VEC4_CMATH_UTILS_H_
#define _VEC4_CMATH_UTILS_H_

#include <cmath>
#include "vec3.h"
#include "vec2.h"

struct vec4
{
	union
	{
		struct { float x, y, z, w; };
		struct { float r, g, b; };
		struct { vec3 xyz; };
		struct { vec2 xy; };
		float v[4];
	};

	vec4() {}
	vec4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}
	vec4(const vec2 &xy, float z, float w) : xy(xy), z(z), w(w) {}
	vec4(const vec3 &xyz, float w) : xyz(xyz), w(w) {}

	static vec4 zero() { return vec4(0, 0, 0, 0); }
	static vec4 affine() { return vec4(0, 0, 0, 1); }
};

const vec4 operator-(const vec4 &v);
const float lengthSqr(const vec4 &v);
const float length(const vec4 &v);
const vec4 normal(const vec4 &v);

const float distanceSqr(const vec4 &l, const vec4 &r);
const float distance(const vec4 &l, const vec4 &r);
const float angleBetween(const vec4 &l, const vec4 &r);
const float dot(const vec4 &l, const vec4 &r);

const vec4 operator+(const vec4 &l, const vec4 &r);
const vec4 operator-(const vec4 &l, const vec4 &r);
const vec4 operator/(const vec4 &l, float r);
const vec4 operator*(const vec4 &l, float r);
const vec4 operator/(float l, vec4 &r);
const vec4 operator*(float l, vec4 &r);

vec4 &operator+=(vec4 &l, const vec4 &r);
vec4 &operator-=(vec4 &l, const vec4 &r);
vec4 &operator/=(vec4 &l, float r);
vec4 &operator*=(vec4 &l, float r);

const bool operator==(const vec4 &l, const vec4 &r);
const bool operator!=(const vec4 &l, const vec4 &r);
const bool operator>=(const vec4 &l, const vec4 &r);
const bool operator<=(const vec4 &l, const vec4 &r);
const bool operator>(const vec4 &l, const vec4 &r);
const bool operator<(const vec4 &l, const vec4 &r);

#endif