#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "config.h"

class Ball : public Entity
{
	float initialSpeed = 60.f;
	float addSpeed = 20.f;
	float maxSpeed = 200.f;
public:
	int ballIndex = 0;
	Ball()
	{
		onBallLeftScreen = nullptr;
		size = { ball_width, ball_height};
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
		newVelocity.x = initialSpeed;
		newVelocity.y = -initialSpeed;
		physics->velocity = newVelocity;
		physics->isActive = true;
		collider->enabled = true;
		physics->collider = collider;
	}
};