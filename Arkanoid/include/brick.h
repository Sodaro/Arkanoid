#pragma once
#include "entity.h"
#include "collision.h"
#include "common.h"
#include "config.h"
#include "game_data.h"

struct RenderComponent;
struct CollisionComponent;

class Brick : public Entity
{
public:
	int score, brickIndex, maxHealth, currentHealth;
	Data::BrickType type;
	actionInt onDestroyCallback;
	Brick();
	void initializeTypeData(Data::BrickType type, Color c1, Color c2, Color o, int score, int maxHealth);
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	void resetHealth();
	
};