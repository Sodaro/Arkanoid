#include "config.h"
#include "entity.h"
#include "physics_component.h"
#include "collision_component.h"

PhysicsComponent::PhysicsComponent()
{
	collider = nullptr;
	pos = nullptr;
	size = velocity = Vector2{ 0,0 };
	isActive = false;
}

PhysicsComponent::PhysicsComponent(CollisionComponent& collider) : collider(&collider)
{
	pos = nullptr;
	size = velocity = Vector2{ 0,0 };
	isActive = false;
}

void PhysicsComponent::update(double dt)
{
	if (reflectOnCollision)
	{
		step(velocity.x * dt, velocity.y * dt);
	}
	else
	{
		moveInsideScreen(velocity.x * dt, velocity.y * dt);
		collider->updateBox();
	}
}

bool PhysicsComponent::moveInsideScreen(float dx, float dy)
{
	float xbounds = 0, ybounds = 0;

	if (size != Vector2{0,0})
	{
		xbounds = (float)size.x / 2;
		ybounds = (float)size.y / 2;
	}
	if (pos->x - xbounds <= 0)
		pos->x = xbounds;
	else if (pos->x + xbounds > game_width)
		pos->x = game_width - xbounds;

	if (pos->y < ybounds)
		pos->y = ybounds;


	bool left = pos->x + dx < xbounds;
	bool right = pos->x + dx >= game_width - xbounds;
	bool up = pos->y + dy < ybounds;

	CollisionParams params;
	if (left || right || up)
	{
		Vector2 side{ 0,0 };
		if (left)
			side.x = -1;
		else if (right)
			side.x = 1;
		else
			side.y = 1;

		params.normal = side;
		collider->owner->onCollision(params);
	}

	pos->x += dx;
	pos->y += dy;
	return true;
}

bool PhysicsComponent::step(float dx, float dy)
{
	if (!isActive || collider == nullptr)
		return false;

	Vector2 newPos = { pos->x + dx, pos->y + dy };

	bool collision = collider->checkCollisions(newPos);
	if (collision)
		return false;

	return moveInsideScreen(dx, dy);
}
