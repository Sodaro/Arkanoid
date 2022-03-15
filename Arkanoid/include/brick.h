#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "collision.h"
#include "common.h"
#include "config.h"
#include "entity_data.h"

class Brick : public Entity
{
public:
	//Brick* bricks;
	int score = 0;
	int brickIndex = 0;
	int health = 1;
	Data::BrickType type;
	actionInt onDestroyCallback;
	Brick()
	{
		type = Data::BrickType::Six;
		//bricks = nullptr;
		onDestroyCallback = nullptr;
		size = { brick_width, brick_height };
	}
	void initializeTypeData(Data::BrickType type, Color c1, Color c2, int score);
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	
};