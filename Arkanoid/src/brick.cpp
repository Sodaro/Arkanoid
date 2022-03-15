#include "brick.h"
#include "config.h"
#include "entity_data.h"
//void Brick::render()
//{
//}

void Brick::initializeTypeData(Data::BrickType type, Color c1, Color c2, int score)
{
	this->type = type;
	this->score = score;
	color1 = c1;
	color2 = c2;
}

void Brick::onCollision(CollisionParams& params)
{
	reduceHealth(1);
}

void Brick::reduceHealth(int amount)
{
	health -= amount;
	if (health <= 0)
	{
		collider->enabled = false;
		renderer->isVisible = false;
		(game->*onDestroyCallback)(brickIndex);
	}
}
