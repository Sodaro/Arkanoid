#include "brick.h"
#include "config.h"
//void Brick::render()
//{
//}

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
