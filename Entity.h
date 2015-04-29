#pragma once 
#include "dep/cmathutils.h"
#include "dep\shapes.h"
#include <vector>

class Entity
{
	float speed;
	vec2 pos;

public:
	int index;
	std::vector<vec2> path;
	std::vector<vec2> smoothPath;

	Entity(float speed, vec2 pos);

	vec2 getPos(){ return pos; }
	void drawEntity(mat4 m, float radius);

	void update(float dt);
	void seek(vec2 &pos, vec2 &vel, vec2 target, float speed, float dt);
};
