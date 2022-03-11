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
	enum class Type { Green, Purple, Blue, Yellow, Red, Gray };
	//Brick* bricks;
	int score = 0;
	int brickIndex = 0;
	int health = 1;
	Type type;
	actionInt onDestroyCallback;
	Brick()
	{
		type = Type::Gray;
		//bricks = nullptr;
		onDestroyCallback = nullptr;
		size = { brick_width, brick_height };
	}
	void initializeTypeData(Type type);
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	
};