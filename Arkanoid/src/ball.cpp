#include "ball.h"
#include "collision.h"
#include <iostream>

void Ball::onCollision(CollisionParams& params)
{
	//std::cout << "contactNormal:{" << params.normal.x << ";" << params.normal.y << "}" << std::endl;
	//std::cout << "vel.x: " << physics->velocity.x << " normal: {" << params.normal.x << ";" << params.normal.y << "}" << std::endl;
	float normalX = params.normal.x;
	float normalY = params.normal.y;
	if (params.contactPoint != Vector2{ 0,0 })
	{
		if (normalX != 0)
			pos.x = params.contactPoint.x + ((size.x / 2 + 2) *params.normal.x);
		else
			pos.y = params.contactPoint.y + ((size.y / 2 + 2) * params.normal.y);

		collider->updateBox();
	}

	if (normalX != 0)
	{
		physics->velocity.x *= -1;
	}
	if (normalY != 0)
	{
		physics->velocity.y *= -1;
	}
}