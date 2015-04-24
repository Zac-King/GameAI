#include "vec2.h"

const vec2 operator-(const vec2 &v) { return v * -1; }
const float lengthSqr(const vec2 &v) { return dot(v,v); }
const float length(const vec2 &v)
{
	return sqrt(lengthSqr(v));
};
const vec2 normal(const vec2 &v) { return v / length(v); };
const float angle(const vec2 &v) { return atan2f(v.y, v.x); };

const vec2 mid(const  vec2 &a, const vec2 &b) { return (a + b) / 2; }

const float distance(const vec2 &l, const vec2 &r) { return length(l - r); }
const float angleBetween(const vec2 &l, const vec2 &r) { return acos(dot(l, r) / (length(l) * length(r))); }
const float dot(const vec2 &l, const vec2 &r) { return l.x*r.x + l.y*r.y; }

const vec2 operator+(const vec2 &l, const vec2 &r) { return { l.x + r.x, l.y + r.y}; }
const vec2 operator-(const vec2 &l, const vec2 &r) { return { l.x - r.x, l.y - r.y }; }
const vec2 operator/(const vec2 &l, float r)	   { return { l.x / r, l.y / r }; }
const vec2 operator*(const vec2 &l, float r)	   { return { l.x * r, l.y * r }; }
const vec2 operator/(float l, vec2 &r)			   { return { l / r.x, l / r.y }; }
const vec2 operator*(float l, vec2 &r)			   { return { l * r.x, l * r.y }; }

vec2 &operator+=(vec2 &l, const vec2 &r) { return l = l + r; }
vec2 &operator-=(vec2 &l, const vec2 &r) { return l = l - r; }
vec2 &operator/=(vec2 &l, float r)		 { return l = l / r; }
vec2 &operator*=(vec2 &l, float r)		 { return l = l * r; }

const bool operator==(const vec2 &l, const vec2 &r) { return l.x == r.x && l.y == r.y; }

const bool operator!=(const vec2 &l, const vec2 &r) { return !(l == r); }
const bool operator>=(const vec2 &l, const vec2 &r) { return lengthSqr(l) >= lengthSqr(r); }
const bool operator<=(const vec2 &l, const vec2 &r) { return lengthSqr(l) <= lengthSqr(r); }
const bool operator>(const vec2 &l, const vec2 &r)  { return lengthSqr(l) < lengthSqr(r); }
const bool operator<(const vec2 &l, const vec2 &r)  { return lengthSqr(l) > lengthSqr(r); }