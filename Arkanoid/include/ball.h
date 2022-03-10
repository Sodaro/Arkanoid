#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"

class Ball : public Entity
{
	float addSpeed = 10.f;
	float maxSpeed = 100.f;
public:
	int ballIndex = 0;
	Ball()
	{
		onBallLeftScreen = nullptr;
		size = { 16,16 };
	}

	actionInt onBallLeftScreen;

	//void setupRenderer()
	//{
	//	renderer->size = size;
	//	renderer->color = &color;
	//	renderer->pos = &pos;
	//}


	void handleOutsideScreen();
	void onCollision(CollisionParams& params) override;

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