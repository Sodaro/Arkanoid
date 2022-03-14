#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "collision.h"
#include "common.h"
#include "config.h"


class Brick : public Entity
{
public:
	//Brick* bricks;
	int score = 0;
	int brickIndex = 0;
	int health = 1;
	BrickType type;
	actionInt onDestroyCallback;
	Brick()
	{
		type = BrickType::Gray;
		//bricks = nullptr;
		onDestroyCallback = nullptr;
		size = { brick_width, brick_height };
	}
	void initializeTypeData(BrickType type);
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	
};