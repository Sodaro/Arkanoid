#include "CollisionComponent.h"
#include "entity.h"

void CollisionComponent::init(ColliderParams params)
{
	this->colliders = params.colliders;
	box = AABB::make_from_position_size(params.pos, params.size);
	this->pos = params.pos;
	this->size = params.size;
	this->numColliders = params.numColliders;
	enabled = false;
	this->owner = params.owner;
}

void CollisionComponent::update()
{
	box = AABB::make_from_position_size(pos, size);
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


		AABB box2 = collider2.box;
		if (aabb_intersect(box, box2))
		{
			collider2.owner->onCollision();
			return true;
		}

	}
	return false;
}
