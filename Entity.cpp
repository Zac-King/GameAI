#include "Entity.h"

Entity::Entity(float speed, vec2 pos) : speed(speed), pos(pos), vel(vec2(0, 0)), roc(false)
{}

void Entity::drawEntity(mat4 m, float radius)
{
	circle r(pos, radius);
	draw_circle(m, r);
}

void Entity::update(float dt)
{
		// Seek

	if (index < smoothPath.size())
	{
		if (distance(smoothPath[index], pos) <= 6) index++;
		if (index < smoothPath.size())
		{
			//pos += normal(smoothPath[index] - pos) * speed * dt;
			seek(pos, vel, smoothPath[index], speed, dt);
		}
	}
}

float min(float a, float b)
{
	return (a > b)  ? a : b;
}

void Entity::seek(vec2 &pos, vec2 &vel, vec2 target, float speed, float dt)
{
		// Seek
	auto force = normal(target - pos);
	force *= speed;
	force -= vel;

		// Integrate
	vel += force * dt;
	vel  = normal(vel) * min(length(vel), speed);
	pos += vel * dt;
}