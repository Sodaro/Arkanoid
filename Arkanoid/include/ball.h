#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"

class Ball : public Entity
{
public:
	Ball()
	{
		size = { 16,16 };
	}
	//void setupRenderer()
	//{
	//	renderer->size = size;
	//	renderer->color = &color;
	//	renderer->pos = &pos;
	//}

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
};