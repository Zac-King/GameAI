#include "vec3.h"

const vec3 operator-(const vec3 &v) { return v * -1; }
const float lengthSqr(const vec3 &v) { return dot(v,v); }
const float length(const vec3 &v) { return sqrt(lengthSqr(v)); };
const vec3 normal(const vec3 &v) { return v / length(v); };

const float distance(const vec3 &l, const vec3 &r) { return length(l - r); }
const float angleBetween(const vec3 &l, const vec3 &r) { return acos(dot(l, r) / (length(l) * length(r))); }
const float dot(const vec3 &l, const vec3 &r) { return l.x*r.x + l.y*r.y + l.z*r.z; }

const vec3 cross(const vec3 &l, const vec3 &r)
{
	return
	   { l.y * r.z - l.z * r.y,
		 l.z * r.x - l.x * r.z,
		 l.x * r.y - l.y * r.x };
}

const vec3 operator+(const vec3 &l, const vec3 &r) { return{ l.x + r.x, l.y + r.y, l.z+r.z }; }
const vec3 operator-(const vec3 &l, const vec3 &r) { return{ l.x - r.x, l.y - r.y, l.z-r.z }; }
const vec3 operator/(const vec3 &l, float r)	   { return{ l.x / r, l.y / r, l.z / r }; }
const vec3 operator*(const vec3 &l, float r)	   { return{ l.x * r, l.y * r, l.z * r }; }
const vec3 operator/(float l, vec3 &r)			   { return{ l / r.x, l / r.y, l / r.z }; }
const vec3 operator*(float l, vec3 &r)			   { return{ l * r.x, l * r.y, l * r.z }; }

vec3 &operator+=(vec3 &l, const vec3 &r) { return l = l + r; }
vec3 &operator-=(vec3 &l, const vec3 &r) { return l = l - r; }
vec3 &operator/=(vec3 &l, float r)		 { return l = l / r; }
vec3 &operator*=(vec3 &l, float r)		 { return l = l * r; }

const bool operator==(const vec3 &l, const vec3 &r) { return l.x == r.x && l.y == r.y && l.z == r.z; }

const bool operator!=(const vec3 &l, const vec3 &r) { return !(l == r); }
const bool operator>=(const vec3 &l, const vec3 &r) { return lengthSqr(l) >= lengthSqr(r); }
const bool operator<=(const vec3 &l, const vec3 &r) { return lengthSqr(l) <= lengthSqr(r); }
const bool operator>(const vec3 &l, const vec3 &r)  { return lengthSqr(l) < lengthSqr(r); }
const bool operator<(const vec3 &l, const vec3 &r)  { return lengthSqr(l) > lengthSqr(r); }