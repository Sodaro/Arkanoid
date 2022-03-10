#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "input.h"
#include "PhysicsComponent.h"
#include "ball.h"
#include "common.h"

class Player : public Entity
{
	Ball* balls;

	int ballIndex = 0;
	const int nrOfBalls;
	const float shootDelay = 0.25f;
	float shootTimer = 0.25f;
public:
	int availableBalls = 1;
	action ballShotCallback;
	CollisionComponent* collider;
	Player(const int nrOfBalls) : nrOfBalls(nrOfBalls)
	{
		pos = { 256,456 };
		size = { 128,24 };
		color = MAGENTA;
		renderer = nullptr;
		collider = nullptr;
		physics = nullptr;
		balls = nullptr;
		ballShotCallback = nullptr;
	}

	Player(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider, Ball* ballsArr, const int nrOfBalls) : nrOfBalls(nrOfBalls)
	{
		this->renderer = renderer;
		this->collider = collider;
		this->physics = physics;

		pos = { 256,456 };
		size = { 128,24 };
		color = MAGENTA;
		this->renderer->isVisible = true;
		setupRenderer();
		balls = ballsArr;
		physics->pos = &pos;
		physics->collider = collider;
		physics->isActive = true;
		physics->reflectOnCollision = false;
		ballShotCallback = nullptr;
	}

	void setColor(Color color)
	{
		this->color = color;
		renderer->color = &this->color;
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