#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "collision.h"
#include "common.h"


class Brick : public Entity
{
public:
	//Brick* bricks;
	int brickIndex = 0;
	int health = 1;
	actionInt onDestroyCallback;
	Brick()
	{
		//bricks = nullptr;
		onDestroyCallback = nullptr;
		size = { 64,28 };
	}
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	
};