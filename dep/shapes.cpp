#include "shapes.h"
#include <iostream>
#include <cassert>
#include "crenderutils.h"
#define NOMINMAX
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>

void debug(char *a, bool todo = true)
{
	std::cerr << (todo ? "TODO: " : "WARNING: ") << a << std::endl;
	assert(!todo);
}

const circle operator*(const mat4 &m, const circle &s)
{	return{ mulaff(m, s.position), length(mul(m, vec2(s.radius, 0))) };	}
const line   operator*(const mat4 &m, const line &s)
{	return {mulaff(m, s.position), mulaff(m, s.end) };	}
const point  operator*(const mat4 &m, const point &s)
{	return {m * s.position };	}
const aabb operator*(const mat4 &m, const aabb &s)
{	return { mulaff(m, s.position), mul(m, s.dimension) };	}


const collision circle_circle(const circle &a, const circle &b)
{
	collision r;
	vec2 diff = a.position - b.position;

	r.normal = normal(diff);
	r.contact = (a.position + b.position) / 2;
	r.depth = a.radius + b.radius - length(diff);
	r.result = r.depth > 0;

	return r;
}

// TODO:
const collision circle_line(const circle &a, const line &b)
{
	collision r;
	debug("circle line");
	return r;
}

const collision circle_aabb(const circle &a, const aabb &b)
{
	collision r;
	debug("circle aabb");
	return r;
}

const collision line_line(const line &a, const line &b)
{
	collision r;

	auto m1 = (a.position.y - a.end.y) / (a.position.x - a.end.x);
	auto m2 = (b.position.y - b.end.y) / (b.position.x - b.end.x);

	auto b1 = a.position.y - m1*a.position.x;
	auto b2 = b.position.y - m2*b.position.x;

	float x = (b2 - b1) / (m1 - m2);
	float y = m1*x + b1;

	if ((a.position.x - a.end.x) == 0) // if a is a vertical line, then there is only 1 possible x value.
	{	x = a.position.x;	y = m2 *x + b2;	}
	if ((b.position.x - b.end.x) == 0)
	{	x = b.position.x;	y = m1 *x + b1;	}

	r.contact = { x, y }; point p(r.contact);
	r.result = circle_point(circle(a.mid(), a.length() / 2), p).result
		    && circle_point(circle(b.mid(), b.length() / 2), p).result;

	if (m1 == m2)
	{
		r.result = false;
		return r;
	}
	return r;
}

const collision line_aabb(const line &a, const aabb &b)
{
	collision r;
	r.result = false;
	
	for (int i = 0; i < 4; ++i)
	{
		r.result = r.result || line_line(a, b.edge(i)).result;
	}

	return r;
}

const collision aabb_aabb(const aabb &a, const aabb &b)
{
	collision r;
	debug("AABB AABB : only result, no normal data", false);

	r.result = 
	!(a.max().x < a.min().x ||
	b.max().x < a.min().x ||
	a.max().y < a.min().y ||
	b.max().y < a.min().y);

	return r;
}




const collision circle_point(const circle &a, const point &b) { return circle_circle(a, b); }
const collision line_point(const line &a, const point &b)	  { return circle_line(b, a); }
const collision point_point(const point &a, const point &b)	  { return circle_circle(a,b); }
const collision point_aabb(const point &a, const aabb &b)	  { return circle_aabb(a, b); }



void draw_line(const mat4 &m, const line &a, const vec4 &color)
{
	glLoadIdentity();
	glLoadMatrixf(m.m);
	glColor4fv(color.v);
	glBegin(GL_LINES);
		glVertex2fv(a.position.v);
		glVertex2fv(a.end.v);
	glEnd();
}

void draw_circle(const mat4 &m, const circle &a, const vec4 &color)
{
	const float step = PI / 12;
	
	glLoadIdentity();
	glLoadMatrixf(m.m);
	glColor4fv(color.v);
	glBegin(GL_LINE_LOOP);
	
	for (float i = 0; i <= 2 * PI; i += step)
		glVertex2fv((a.position + vec2(cos(i), sin(i))*a.radius).v);
	glEnd();
}
void draw_point(const mat4 &m, const point &a, const vec4 &color)
{
	draw_circle(m, circle(a.position, 1), color);
	draw_circle(m,circle(a.position, a.drawsize), color);
}
void draw_aabb(const mat4 &m, const aabb &a, const vec4 &color)
{
	for (int i = 0; i < 4; ++i)
		draw_line(m, a.edge(i), color);
}