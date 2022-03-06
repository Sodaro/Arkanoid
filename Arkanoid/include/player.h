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
	
	Ball* balls;

	int ballIndex = 0;
	const int nrOfBalls;
	Color color;
	float shootDelay = 1;
public:
	CollisionComponent* collider;
	Vector2 pos;
	Vector2 size{128,24};
	Player(const int nrOfBalls) : nrOfBalls(nrOfBalls)
	{
		pos = Vector2{ 256,456 };
		color = MAGENTA;
		renderer = nullptr;
		collider = nullptr;
		physics = nullptr;
		balls = nullptr;
	}

	Player(RenderComponent& renderer, PhysicsComponent& physics, CollisionComponent& collider, Ball* ballsArr, const int nrOfBalls) : renderer(&renderer), physics(&physics),
		collider(&collider), nrOfBalls(nrOfBalls)
	{
		pos = Vector2{ 256,456 };
		color = MAGENTA;
		renderer.isVisible = true;
		renderer.color = &color;
		renderer.pos = &pos;
		renderer.size = size;
		balls = ballsArr;

		physics.pos = &pos;
		physics.collider = &collider;
		physics.isActive = true;
		physics.reflectOnCollision = false;
	}
	void assignRenderer(RenderComponent& renderer)
	{
		color = MAGENTA;
		this->renderer = &renderer;
		renderer.isVisible = true;
		renderer.size = size;
		renderer.color = &color;
		renderer.pos = &pos;
	}
	void assignPhysics(PhysicsComponent& physics)
	{
		this->physics = &physics;
		physics.pos = &pos;
		physics.isActive = true;
		physics.reflectOnCollision = false;
	}
	void assignCollider(CollisionComponent& collider)
	{
		this->collider = &collider;
	}

	Player& operator= (Player&& p) noexcept
	{
		this->renderer = p.renderer;
		this->physics = p.physics;
		this->collider = p.collider;
		this->pos = p.pos;

		renderer->pos = &pos;
		physics->pos = &pos;
		collider->pos = &pos;
		
		this->size = p.size;
		this->balls = p.balls;

		p.renderer = nullptr;
		p.collider = nullptr;
		p.physics = nullptr;
		p.balls = nullptr;

		return *this;
	}

	void update(float dt);

};