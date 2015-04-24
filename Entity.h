#pragma once 
#include "dep/cmathutils.h"
#include "dep\shapes.h"

class Entity
{
	float speed;
	vec2 pos;

public:
	int index;
	std::vector<vec2> path;
	std::vector<vec2> smoothPath;
	Entity(float speed, vec2 pos) : speed(speed), pos(pos)
	{}
	vec2 getPos(){ return pos; }
	void drawEntity(mat4 m, float radius)	
	{
		circle r(pos, radius);
		draw_circle(m,r); 
	}

	void update(float dt)
	{
		
		if (index < smoothPath.size())
		{
			if (distance(smoothPath[index], pos) <= 6) index++;
			if (index < smoothPath.size())
				pos += normal(smoothPath[index] - pos) * speed * dt;			
		}
	}
};