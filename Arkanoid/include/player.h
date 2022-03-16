#pragma once
#include "entity.h"
#include "input.h"
#include "ball.h"
#include "common.h"
#include "config.h"


struct PhysicsComponent;
struct RenderComponent;
struct CollisionComponent;
class Player : public Entity
{
	Ball* balls;
	int ballIndex = 0;
	const int nrOfBalls;

public:
	int availableBalls = 1;
	action ballShotCallback;
	CollisionComponent* collider;
	Player(const int nrOfBalls);

	Player(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider, Ball* ballsArr, const int nrOfBalls);

	void setColor(Color c1, Color c2, Color o);

	Player& operator = (Player&& p) noexcept;

	void update(float dt);

};