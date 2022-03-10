#include "ball.h"
#include "collision.h"
#include <iostream>
#include "player.h"
#include "config.h"

void Ball::handleOutsideScreen()
{
	if (pos.y > game_height && physics->isActive)
	{
		onBallLeftScreen(ballIndex);
		disable();
	}
}

void Ball::onCollision(CollisionParams& params)
{
	if (dynamic_cast<Player*>(params.colliderObject) != nullptr)
	{
		//ty ruta!
		Vector2 ballToPlayer = params.colliderObject->pos - pos + Vector2{0, size.y};
		float len = sqrtf(ballToPlayer.x * ballToPlayer.x + ballToPlayer.y * ballToPlayer.y);
		Vector2 dir = ballToPlayer / len;
		Vector2 velocity = physics->velocity;
		if (dir.y > 0.75)
		{
			dir.y = 0.75;
			dir.x = velocity.x > 0 ? -0.35f : 0.35f;
		}
		float speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
		if (speed < maxSpeed)
			speed += addSpeed;

		//printf("%f, %f\n", dir.x, dir.y);
		physics->velocity = (dir*-1) * speed;
		return;
	}

	Vector2 normal = params.normal;
	if (params.contactPoint != Vector2{ 0,0 })
	{
		if (normal.x != 0)
			pos.x = params.contactPoint.x + ((size.x / 2 + 2) * normal.x);
		else
			pos.y = params.contactPoint.y + ((size.y / 2 + 2) * normal.y);

		collider->updateBox();
	}

	if (normal.x != 0)
	{
		physics->velocity.x *= -1;
	}
	if (normal.y != 0)
	{
		physics->velocity.y *= -1;
	}
}