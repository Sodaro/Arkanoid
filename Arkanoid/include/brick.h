#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "collision.h"


class Brick : public Entity
{
public:
	Brick* bricks;
	int brickIndex = 0;
	int health = 1;
	typedef void (*func)(int);
	func onDestroyCallback;
	Brick()
	{
		bricks = nullptr;
		onDestroyCallback = nullptr;
		size = { 64,28 };
	}
	void onCollision(Vector2 normal) override;
	void reduceHealth(int amount);
	
};