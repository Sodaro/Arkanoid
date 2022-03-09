
#include "config.h"
#include "entity.h"

#include "PhysicsComponent.h"
#include "CollisionComponent.h"

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

		step(velocity.x * dt, velocity.y * dt);
		//step(0.f, velocity.y * dt);
		//if (!step(0.f, velocity.y * dt))
			//velocity.y = -velocity.y * 1.0f;
	}
	else
	{
		moveInsideScreen(velocity.x * dt, velocity.y * dt);
		collider->updateBox();
	}

	//separating step into y and x separately, we're the ball can slide up and down bricks instead of stopping
}

bool PhysicsComponent::moveInsideScreen(float dx, float dy)
{
	if (pos->x < 0)
		pos->x = 0;
	else if (pos->x > game_width)
		pos->x = game_width;
	if (pos->y < 0)
		pos->y = 0;
	else if (pos->y > game_height)
		pos->y = game_height;


	bool left = pos->x + dx < 0;
	bool right = pos->x + dx >= game_width;
	bool up = pos->y + dy < 0;
	bool down = pos->y + dy >= game_height;
	CollisionParams params;
	if (left || right || up || down)
	{
		Vector2 side{ 0,0 };
		if (left)
			side.x = -1;
		else if (right)
			side.x = 1;
		else if (up)
			side.y = 1;
		else
			side.y = 1;
		params.normal = side;
		collider->owner->onCollision(params);
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
