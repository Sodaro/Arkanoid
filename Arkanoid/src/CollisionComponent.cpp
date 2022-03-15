#include "CollisionComponent.h"
#include "entity.h"
#include "raymath.h"
#include <iostream>
void CollisionComponent::init(ColliderParams params)
{
	this->colliders = params.colliders;
	this->isBox = params.isBox;
	if (params.isBox)
		box = AABB::make_from_position_size(params.pos, params.size);
	else
		circle = Circle::make_from_position_size(params.pos, params.size);
	
	this->pos = params.pos;
	this->size = params.size;
	this->numColliders = params.numColliders;
	enabled = true;
	this->owner = params.owner;
}

void CollisionComponent::updateBox()
{
	box = AABB::make_from_position_size(pos, size);
}

CollisionParams calculateCollisionData(Entity* a, Entity* b)
{
	Vector2 center, bounds;
	center = b->pos;
	bounds = b->size / 2;
	Vector2 distanceToPositiveBounds = center + bounds - a->pos;
	Vector2 distanceToNegativeBounds = (center - bounds - a->pos);
	distanceToNegativeBounds = distanceToNegativeBounds * -1;
	float smallestX = fmin(distanceToPositiveBounds.x, distanceToNegativeBounds.x);
	float smallestY = fmin(distanceToPositiveBounds.y, distanceToNegativeBounds.y);
	float smallestDistance = fmin(smallestX, smallestY);

	CollisionParams params;

	if (smallestDistance == distanceToPositiveBounds.x)
	{
		params.contactPoint.x = center.x + bounds.x;
		params.normal.x = 1;
	}
	else if (smallestDistance == distanceToNegativeBounds.x)
	{
		params.contactPoint.x = center.x - bounds.x;
		params.normal.x = -1;
	}	

	if (smallestDistance == distanceToPositiveBounds.y)
	{
		params.contactPoint.y = center.y + bounds.y;
		params.normal.y = 1;
	}
	else
	{
		params.contactPoint.y = center.y - bounds.y;
		params.normal.y = -1;
	}

	if (params.contactPoint.y == 0)
		params.contactPoint.y = a->pos.y;
	if (params.contactPoint.x == 0)
		params.contactPoint.x = a->pos.x;

	params.colliderObject = b;

	return params;
}

bool CollisionComponent::checkCollisions(Vector2 newPos)
{
	if (!enabled)
		return false;

	box = AABB::make_from_position_size(&newPos, size);
	for (int i = 0; i < numColliders; ++i)
	{
		if (this == &colliders[i])
			continue;

		CollisionComponent collider2 = colliders[i];

		if (!collider2.enabled)
			continue;

		if (aabb_intersect(box, collider2.box))
		{
			CollisionParams params = calculateCollisionData(owner, collider2.owner);
			this->owner->onCollision(params);
			params.contactPoint = Vector2{ 0,0 };
			params.colliderObject = owner;
			collider2.owner->onCollision(params);

			return true;
		}
	}
	return false;
}