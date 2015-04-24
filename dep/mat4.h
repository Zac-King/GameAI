#pragma once
#ifndef _MAT4_CMATH_UTILS_H_
#define _MAT4_CMATH_UTILS_H_

#include "vec3.h"
#include "vec4.h"

struct mat4
{
	union
	{
		struct { float mm[4][4]; };
		struct { float m[16]; };
		struct { vec4 c[4]; };
		struct
		{
			union { struct { vec4 c1; }; struct{ vec3 right;    }; };
			union { struct { vec4 c2; }; struct{ vec3 up;       }; };
			union { struct { vec4 c3; }; struct{ vec3 forward;  }; };
			union { struct { vec4 c4; }; struct{ vec3 position; }; };		
		};
	};

	mat4(){}
	mat4(vec4 c1, vec4 c2, vec4 c3, vec4 c4) : c1(c1), c2(c2), c3(c3), c4(c4) {}

	static const mat4 identity() { return { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} }; }
	static const mat4 zero() { return{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }; }

	static const mat4 scale2D(const vec2 &s) { return{ { s.x, 0, 0, 0 }, { 0, s.y, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } }; }
	static const mat4 translate2D(const vec2 &t) { return{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { t.x, t.y, 0, 1 } }; }
	static const mat4 rotate2D(float a) { return{ { cos(a), -sin(a), 0, 0 }, { sin(a), cos(a), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } }; }

	static const mat4 ortho(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 r = zero();
		r.m[0]  = 2.f / (right - left);
		r.m[5]  = 2.f / (top - bottom);
		r.m[10] = 2.f / (far - near);		
		r.m[12] = -1 * ((right + left) / (right - left));
		r.m[13] = -1 * ((top + bottom) / (top - bottom));
		r.m[14] = -1 * ((far + near) / (far - near));
		r.m[15] = 1;
		return r;
	}
};


const mat4 transpose(const mat4 &m);
const mat4 operator*(const mat4 &l, const mat4 &r);
const vec4 operator*(const mat4 &l, const vec4 &r);

const vec3 mul(const mat4 &l, const vec3 &r);
const vec3 mulaff(const mat4 &l, const vec3 &r);

const vec2 mul(const mat4 &l, const vec2 &r);
const vec2 mulaff(const mat4 &l, const vec2 &r);



mat4 &operator*=(mat4 &l, const mat4 &r);

#endif