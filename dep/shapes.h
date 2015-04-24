#pragma once
#include "cmathutils.h"
#include "crenderutils.h"


struct circle
{
	vec2 position;
	float radius;
	circle(const vec2 &p, float r) : position(p), radius(r) {}
};
struct line
{
	vec2 position;
	vec2 end;
	line(const vec2 &p, const vec2 &p2) : position(p), end(p2) {}
	const vec2 mid() const { return (position + end) / 2; }
	const float length() const { return distance(position, end); }
};

struct point 
{
	vec2 position;
	float tolerance;
	float drawsize;
	point(const vec2 &p, float tolerance = 0, float drawsize = 4) : position(p), tolerance(tolerance), drawsize(drawsize) {}
	operator const circle() const { return circle(position, tolerance); }
};


struct aabb
{
	vec2 position, dimension;
	const vec2 min() const { return position - dimension / 2; }
	const vec2 max() const { return position + dimension / 2; }
	const line edge(unsigned direction) const
	{
		switch (direction % 4)
		{
		case 0: return line(max(), vec2(min().x, max().y));
		case 1: return line(max(), vec2(max().x, min().y));
		case 2: return line(min(), vec2(max().x, min().y));
		case 3: return line(min(), vec2(min().x, max().y));
		}
	}
	aabb(const vec2 &p, const vec2 &d) : position(p), dimension(d) {}
};

struct collision
{
	bool result;
	vec2 normal;
	vec2 contact;
	float depth;
};


const circle operator*(const mat4 &m, const circle &s);
const line   operator*(const mat4 &m, const line &s);
const point  operator*(const mat4 &m, const point &s);
const aabb   operator*(const mat4 &m, const aabb &s);


const collision circle_circle(const circle &a, const circle &b);
const collision circle_line(const circle &a, const line &b);
const collision circle_point(const circle &a, const point &b);
const collision circle_aabb(const circle &a, const aabb &b);

const collision line_line(const line &a, const line &b);
const collision line_point(const line &a, const point &b);
const collision line_aabb(const line &a, const aabb &b);

const collision point_point(const point &a, const point &b);
const collision point_aabb(const point &a, const aabb &b);

const collision aabb_aabb(const aabb &a, const aabb &b);

void draw_circle(const mat4 &m, const circle &a, const vec4 &color = vec4(1,1,1,1));
void draw_line(const mat4 &m, const line &a, const vec4 &color = vec4(1, 1, 1, 1));
void draw_point(const mat4 &m, const point &a, const vec4 &color = vec4(1, 1, 1, 1));
void draw_aabb(const mat4 &m, const aabb &a, const vec4 &color = vec4(1, 1, 1, 1));