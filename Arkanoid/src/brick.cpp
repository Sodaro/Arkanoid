#include "brick.h"
#include "config.h"
//void Brick::render()
//{
//}

void Brick::onCollision()
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
		int aboveIndex = brickIndex - bricksPerRow;
		int leftIndex = brickIndex - 1;
		int rightIndex = brickIndex + 1;
		if (aboveIndex >= 0)
		{
			if (bricks[aboveIndex].health > 0)
				bricks[aboveIndex].collider->enabled = true;
		}
		if (leftIndex >= 0)
		{
			if (bricks[leftIndex].health > 0)
				bricks[leftIndex].collider->enabled = true;
		}
		if (rightIndex < bricksPerRow)
		{
			if (bricks[rightIndex].health > 0)
				bricks[rightIndex].collider->enabled = true;
		}
	}
}
