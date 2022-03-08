#include "ball.h"
#include "collision.h"
#include <iostream>

void Ball::onCollision(Vector2 normal)
{
	std::cout << "vel.x: " << physics->velocity.x << " normal.x: " << normal.x << std::endl;
	if (normal.x != 0)
	{
		physics->velocity.x *= -1;
	}
	else
	{
		physics->velocity.y *= -1;
	}
}