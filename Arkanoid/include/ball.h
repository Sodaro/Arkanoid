#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include <iostream>

class Ball
{
private:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	CollisionComponent* collider;

public:
	Color color;
	Vector2 pos{ 0,0 };
	Vector2 size{ 16,16 };
	Ball()
	{
		color = WHITE;
		renderer = nullptr;
		physics = nullptr;
		collider = nullptr;
	}
	Ball(RenderComponent& renderer, PhysicsComponent& physics, CollisionComponent& collider) : renderer(&renderer), physics(&physics), collider(&collider)
	{
		//std::cout << &x << std::endl;
		renderer.isVisible = true;
		physics.collider = &collider;
		color = WHITE;
		physics.pos = &pos;
		setupRenderer();

	}
	void setupRenderer()
	{
		renderer->size = size;
		renderer->color = &color;
		renderer->pos = &pos;
		//std::cout << &x << std::endl;
	}
	void setActive()
	{
		renderer->isVisible = true;
		Vector2 newVelocity;
		newVelocity.x = 40;
		newVelocity.y = -40;
		physics->velocity = newVelocity;
		physics->isActive = true;
		collider->enabled = true;
		physics->collider = collider;
	}

	void setup(RenderComponent& renderer, PhysicsComponent& physics, CollisionComponent& collider)
	{
		this->renderer = &renderer;
		this->physics = &physics;
		this->collider = &collider;
		setupRenderer();
		physics.pos = &pos;
	}
	void assignRenderer(RenderComponent& renderer)
	{
		this->renderer = &renderer;
		renderer.isVisible = true;
		setupRenderer();
	}
	void assignPhysics(PhysicsComponent& physics)
	{
		this->physics = &physics;
		physics.pos = &pos;
	}
	void assignCollider(CollisionComponent& collider)
	{
		this->collider = &collider;
	}

};