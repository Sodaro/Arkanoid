#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"


class Ball
{
private:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	CollisionComponent* collider;

public:
	int width = 16, height = 16;
	Color color;
	int x = 0, y = 0;
	Ball()
	{
		color = WHITE;
		renderer = nullptr;
		physics = nullptr;
	};
	Ball(RenderComponent& renderer, PhysicsComponent &physics) : renderer(&renderer), physics(&physics)
	{
		color = WHITE;
	};
	void setActive()
	{
		renderer->isVisible = true;
		Vector2 newVelocity;
		newVelocity.x = 100;
		newVelocity.y = -100;
		physics->velocity = newVelocity;
	}
	void assignRenderer(RenderComponent& renderer)
	{
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

};