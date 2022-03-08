#include "CollisionComponent.h"
#include "entity.h"
#include "raymath.h"
#include <iostream>
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

Vector2 calculateCollisionNormal(Entity* a, Entity* b, Rectangle& interesection)
{
	float ax = interesection.x + interesection.width;
	float ay = interesection.y + interesection.height;
	float sx = a->pos.x < b->pos.x ? -1.0f : 1.0f;
	float sy = a->pos.y < b->pos.y ? -1.0f : 1.0f;

	if (ax <= ay)
		return Vector2{ sx, 0.0f };
	else
		return Vector2{0, sy};
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
		Rectangle overlap;

		if (aabb_get_overlapping_area(box, box2, overlap))
		{
			Vector2 collisionNormal = calculateCollisionNormal(owner, collider2.owner, overlap);
			draw_rect(overlap);
			//Vector2 collisionNormal2 = calculateCollisionNormal(owner, collider2.owner);
			//float x, y;
			//x = box.centerX < box2.centerX ? -1.f : 1.f;
			//y = box.centerY < box2.centerY ? -1.f : 1.f;
			//dot


			//if (x <= y)
			//	collisionNormal

			collider2.owner->onCollision(collisionNormal);
			this->owner->onCollision(collisionNormal);
			return true;
		}

	}
	return false;
}
