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
	char key;
	//Data::BrickType type;
	actionInt onDestroyCallback;
	Brick();
	void initializeTypeData(char key, Color c1, Color c2, Color o, int score, int maxHealth);
	void onCollision(CollisionParams& params) override;
	void reduceHealth(int amount);
	void resetHealth();
	
};