#pragma once
#include "entity.h"
#include "config.h"

struct PhysicsComponent;
struct RenderComponent;
struct CollisionComponent;

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

	void setActive();
};