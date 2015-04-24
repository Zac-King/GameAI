#include "mat4.h"



const mat4 transpose(const mat4 &m)
{
	return
		{ {m.m[0],m.m[4],m.m[8],m.m[12]},
		  {m.m[1],m.m[5],m.m[9],m.m[13]},
		  {m.m[2],m.m[6],m.m[10],m.m[14]},
		  {m.m[3],m.m[7],m.m[11],m.m[15]}};
	
}

const mat4 operator*(const mat4 &l, const mat4 &r)
{
	mat4 eval = mat4::zero();

	for (int i = 0; i < 4; i++)			
		for (int j = 0; j < 4; j++)		
			for (int k = 0; k < 4; k++)
				eval.m[4 * i + j] += l.m[4 * i + k] * r.m[4 * k + j];

	return eval;
}

const vec4 operator*(const mat4 &lin, const vec4 &r)
{
	mat4 l = transpose(lin);
	return { dot(r, l.c1), dot(r, l.c2), dot(r, l.c3), dot(r, l.c4) };
}

const vec3 mul(const mat4 &lin, const vec3 &rin)
{
	mat4 l = transpose(lin);
	vec4 r = {rin,0};
	return { dot(r, l.c1), dot(r, l.c2), dot(r, l.c3) };
}
const vec3 mulaff(const mat4 &lin, const vec3 &rin)
{
	mat4 l = transpose(lin);
	vec4 r = { rin, 1 };
	return{ dot(r, l.c1), dot(r, l.c2), dot(r, l.c3) };
}

const vec2 mul(const mat4 &lin, const vec2 &rin)
{
	mat4 l = transpose(lin);
	vec4 r = { rin, 0, 0 };
	return{ dot(r, l.c1), dot(r, l.c2) };

}
const vec2 mulaff(const mat4 &lin, const vec2 &rin)
{
	mat4 l = transpose(lin);
	vec4 r = { rin, 0, 1 };
	return{ dot(r, l.c1), dot(r, l.c2) };
}

mat4 &operator*=(mat4 &l, const mat4 &r)
{
	return l = l * r;
}