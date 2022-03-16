#include "ball.h"
#include "collision.h"
#include <iostream>
#include "player.h"
#include "raymath.h"
#include "physics_component.h"
#include "render_component.h"
#include "collision_component.h"

void Ball::handleOutsideScreen()
{
	if (pos.y > game_height && physics->isActive)
	{
		(game->*onBallLeftScreen)(ballIndex);
		disable();
	}
}

void Ball::onCollision(CollisionParams& params)
{

	Vector2 velocity = physics->velocity;
	float speed = sqrtf(physics->velocity.x * physics->velocity.x + physics->velocity.y * physics->velocity.y);
	if (dynamic_cast<Player*>(params.colliderObject) != nullptr)
	{
		Vector2 ballToPlayer = params.colliderObject->pos - pos + Vector2{0, size.y};
		float len = sqrtf(ballToPlayer.x * ballToPlayer.x + ballToPlayer.y * ballToPlayer.y);
		Vector2 dir = ballToPlayer / len;
		if (dir.y > 0.75f)
		{
			dir.y = 0.75f;
			dir.x = velocity.x > 0 ? -0.35f : 0.35f;
		}
		if (speed < maxSpeed)
		{
			speed += addSpeed;
			if (speed > maxSpeed)
				speed = maxSpeed;
		}
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
	else if (normal.y != 0)
	{
		physics->velocity.y *= -1;
	}
}

void Ball::setActive()
{
	renderer->isVisible = true;
	Vector2 newVelocity = { initialSpeed, -initialSpeed };
	physics->velocity = newVelocity;
	physics->isActive = true;
	collider->enabled = true;
	physics->collider = collider;
}
