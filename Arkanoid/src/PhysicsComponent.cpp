#include "PhysicsComponent.h"
#include "config.h"
#include "entity.h"

PhysicsComponent::PhysicsComponent()
{
	collider = nullptr;
	pos = nullptr;
	velocity = Vector2{ 0,0 };
	isActive = false;
}

PhysicsComponent::PhysicsComponent(CollisionComponent& collider) : collider(&collider)
{
	pos = nullptr;
	velocity = Vector2{ 0,0 };
	isActive = false;
}

void PhysicsComponent::update(double dt)
{
	if (reflectOnCollision)
	{
		//if (!step(velocity.x * dt, 0.f))
			//velocity.x = -velocity.x * 1.0f;

		step(velocity.x * dt, 0.f);
		step(0.f, velocity.y * dt);
		//if (!step(0.f, velocity.y * dt))
			//velocity.y = -velocity.y * 1.0f;
	}
	else
	{
		moveInsideScreen(velocity.x * dt, velocity.y * dt);
		collider->update();
	}

	//separating step into y and x separately, we're the ball can slide up and down bricks instead of stopping
}

bool PhysicsComponent::moveInsideScreen(float dx, float dy)
{
	bool left = pos->x + dx < 0;
	bool right = pos->x + dx >= game_width;
	bool up = pos->y + dy < 0;
	bool down = pos->y + dy >= game_height;
	if (left || right || up || down)
	{
		Vector2 side{ 0,0 };
		if (left)
			side.x = -1;
		else if (right)
			side.x = 1;
		else if (up)
			side.y = -1;
		else
			side.y = 1;
		collider->owner->onCollision(side);
		return false;
	}

	pos->x += dx;
	pos->y += dy;
	return true;
}

bool PhysicsComponent::step(float dx, float dy)
{
	if (!isActive || collider == nullptr)
		return false;

	Vector2 newPos;
	newPos.x = pos->x + dx;
	newPos.y = pos->y + dy;

	bool collision = collider->checkCollisions(newPos);
	if (collision)
		return false;

	return moveInsideScreen(dx, dy);
}
