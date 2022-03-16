#include "brick.h"
#include "config.h"
#include "collision_component.h"
#include "render_component.h"

Brick::Brick()
{
	score = 0, brickIndex = 0, maxHealth = 1, currentHealth = 1;
	type = Data::BrickType::Six;
	onDestroyCallback = nullptr;
	size = { brick_width, brick_height };
}

void Brick::initializeTypeData(Data::BrickType type, Color c1, Color c2, Color o, int score, int maxHealth)
{
	this->type = type;
	this->score = score;
	this->maxHealth = maxHealth;
	color1 = c1;
	color2 = c2;
	outline = o;
}

void Brick::onCollision(CollisionParams& params)
{
	reduceHealth(1);
}

void Brick::reduceHealth(int amount)
{
	currentHealth -= amount;
	if (currentHealth <= 0)
	{
		collider->enabled = false;
		renderer->isVisible = false;
		(game->*onDestroyCallback)(brickIndex);
	}
}

void Brick::resetHealth()
{
	currentHealth = maxHealth;
}
