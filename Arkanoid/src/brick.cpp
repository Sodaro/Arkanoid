#include "brick.h"
#include "config.h"
//void Brick::render()
//{
//}

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
		onDestroyCallback(brickIndex);
	}
}
