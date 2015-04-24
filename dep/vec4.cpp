#include "vec4.h"

const vec4 operator-(const vec4 &v) { return v * -1; }
const float lengthSqr(const vec4 &v) { return dot(v, v); }
const float length(const vec4 &v) { return sqrt(lengthSqr(v)); };
const vec4 normal(const vec4 &v) { return v / length(v); };

const float distance(const vec4 &l, const vec4 &r) { return length(l - r); }
const float angleBetween(const vec4 &l, const vec4 &r) { return acos(dot(l, r) / (length(l) * length(r))); }
const float dot(const vec4 &l, const vec4 &r) { return l.x*r.x + l.y*r.y + l.z*r.z + l.w*r.w; }


const vec4 operator+(const vec4 &l, const vec4 &r) { return{ l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w }; }
const vec4 operator-(const vec4 &l, const vec4 &r) { return{ l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w }; }
const vec4 operator/(const vec4 &l, float r)	   { return{ l.x / r, l.y / r, l.z / r, l.w / r }; }
const vec4 operator*(const vec4 &l, float r)	   { return{ l.x * r, l.y * r, l.z * r, l.w * r }; }
const vec4 operator/(float l, vec4 &r)			   { return{ l / r.x, l / r.y, l / r.z, l / r.w }; }
const vec4 operator*(float l, vec4 &r)			   { return{ l * r.x, l * r.y, l * r.z, l * r.w }; }

vec4 &operator+=(vec4 &l, const vec4 &r) { return l = l + r; }
vec4 &operator-=(vec4 &l, const vec4 &r) { return l = l - r; }
vec4 &operator/=(vec4 &l, float r)		 { return l = l / r; }
vec4 &operator*=(vec4 &l, float r)		 { return l = l * r; }

const bool operator==(const vec4 &l, const vec4 &r) { return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w; }

const bool operator!=(const vec4 &l, const vec4 &r) { return !(l == r); }
const bool operator>=(const vec4 &l, const vec4 &r) { return lengthSqr(l) >= lengthSqr(r); }
const bool operator<=(const vec4 &l, const vec4 &r) { return lengthSqr(l) <= lengthSqr(r); }
const bool operator>(const vec4 &l, const vec4 &r)  { return lengthSqr(l) < lengthSqr(r); }
const bool operator<(const vec4 &l, const vec4 &r)  { return lengthSqr(l) > lengthSqr(r); }