#pragma once
#ifndef _VEC2_CMATH_UTILS_H_
#define _VEC2_CMATH_UTILS_H_
#include <cmath>

struct vec2
{
	union
	{
		struct { float x, y; };
		struct { float s, t; };
		float v[2];
	};
	vec2() {}
	vec2(float x, float y) :x(x), y(y) {}
	static vec2 zero() { return vec2(0, 0); }
	static vec2 fromAngle(float a) { return vec2(cos(a), sin(a)); }
};


const vec2 operator-(const vec2 &v);
const float lengthSqr(const vec2 &v);
const float length(const vec2 &v);
const vec2 normal(const vec2 &v);
const float angle(const vec2 &v);

const float distanceSqr(const vec2 &l, const vec2 &r);
const float distance(const vec2 &l, const vec2 &r);
const float angleBetween(const vec2 &l, const vec2 &r);
const float dot(const vec2 &l, const vec2 &r);

const vec2 mid(const  vec2 &a, const vec2 &b);

const vec2 operator+(const vec2 &l, const vec2 &r);
const vec2 operator-(const vec2 &l, const vec2 &r);
const vec2 operator/(const vec2 &l, float r);
const vec2 operator*(const vec2 &l, float r);
const vec2 operator/(float l, vec2 &r);
const vec2 operator*(float l, vec2 &r);

vec2 &operator+=(vec2 &l, const vec2 &r);
vec2 &operator-=(vec2 &l, const vec2 &r);
vec2 &operator/=(vec2 &l, float r);
vec2 &operator*=(vec2 &l, float r);

const bool operator==(const vec2 &l, const vec2 &r);
const bool operator!=(const vec2 &l, const vec2 &r);
const bool operator>=(const vec2 &l, const vec2 &r);
const bool operator<=(const vec2 &l, const vec2 &r);
const bool operator>(const vec2 &l, const vec2 &r);
const bool operator<(const vec2 &l, const vec2 &r);

#endif