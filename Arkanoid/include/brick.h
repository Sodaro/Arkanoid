#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "collision.h"
#include "common.h"
#include "config.h"
#include "game_data.h"


class Brick : public Entity
{
public:
	//Brick* bricks;
	int score = 0;
	int brickIndex = 0;
	int maxHealth = 1, currentHealth = 1;
	Data::BrickType type;
	actionInt onDestroyCallback;
	Brick()
	{
		type = Data::BrickType::Six;
		//bricks = nullptr;
		onDestroyCallback = nullptr;
		size = { brick_width, brick_height };
	}
	void initializeTypeData(Data::BrickType type, Color c1, Color c2, Color o, int score, int maxHealth);
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	void resetHealth();
	
};