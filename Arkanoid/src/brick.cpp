#include "brick.h"
#include "config.h"
//void Brick::render()
//{
//}

void Brick::initializeTypeData(Type type)
{
	switch (type)
	{
	case Brick::Type::Green:
		color = neon_green;
		score = brick_green_score;
		break;
	case Brick::Type::Purple:
		color = neon_purple;
		score = brick_purple_score;
		break;
	case Brick::Type::Blue:
		color = neon_blue;
		score = brick_blue_score;
		break;
	case Brick::Type::Yellow:
		color = neon_yellow;
		score = brick_yellow_score;
		break;
	case Brick::Type::Red:
		color = neon_red;
		score = brick_red_score;
		break;
	case Brick::Type::Gray:
		color = neon_gray;
		score = brick_gray_score;
		health = 2;
		break;
	default:
		break;
	}
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
