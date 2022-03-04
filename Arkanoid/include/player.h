#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "input.h"
#include "PhysicsComponent.h"
#include "ball.h"

class Player
{
	RenderComponent* renderer;
	PhysicsComponent* physics;
	CollisionComponent* collider;
	Ball* balls;

	int ballIndex = 0;
	const int nrOfBalls;
	Color color;
	float shootDelay = 1;
public:
	int x = 256, y = 456, width = 128, height = 24;
	Player(const int nrOfBalls) : nrOfBalls(nrOfBalls)
	{
		color = MAGENTA;
		renderer = nullptr;
		collider = nullptr;
		physics = nullptr;
		balls = nullptr;
	}

	Player(RenderComponent& renderer, PhysicsComponent& physics, CollisionComponent& collider, Ball* ballsArr, const int nrOfBalls) : renderer(&renderer), physics(&physics),
		collider(&collider), nrOfBalls(nrOfBalls)
	{
		color = MAGENTA;
		renderer.isVisible = true;
		renderer.color = &color;
		renderer.x = &x;
		renderer.y = &y;
		renderer.width = width;
		renderer.height = height;
		balls = ballsArr;

		physics.x = &x;
		physics.y = &y;
	}
	void assignRenderer(RenderComponent& renderer)
	{
		color = MAGENTA;
		this->renderer = &renderer;
		renderer.isVisible = true;
		renderer.width = width;
		renderer.height = height;
		renderer.color = &color;
		renderer.x = &x;
		renderer.y = &y;
	}
	void assignPhysics(PhysicsComponent& physics)
	{
		this->physics = &physics;
		physics.x = &x;
		physics.y = &y;
	}
	void assignCollider(CollisionComponent& collider)
	{
		this->collider = &collider;
	}

	void update(float dt);

};