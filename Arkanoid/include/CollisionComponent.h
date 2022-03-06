#pragma once
#include "common.h"
#include "collision.h"

struct CollisionComponent
{

	struct ColliderParams
	{
		vec2_ptr pos, size;
		CollisionComponent* colliders;
		int numColliders;
		ColliderParams(CollisionComponent* p_colliders, const int p_numColliders) : colliders(p_colliders), numColliders(p_numColliders)
		{
			pos = size = nullptr;
		}
	};

	CollisionComponent* colliders = nullptr;
	int numColliders = 0;

	bool enabled = false;

	vec2_ptr pos = nullptr, size = nullptr;

	AABB box{0,0,0,0};
	void init(ColliderParams params)
	{
		this->colliders = params.colliders;
		box = AABB::make_from_position_size(params.pos, params.size);
		this->pos = params.pos;
		this->size = params.size;
		this->numColliders = params.numColliders;
		enabled = true;
	}

	void update()
	{
		box = AABB::make_from_position_size(pos, size);
	}

	bool checkCollisions(Vector2 newPos)
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
				return true;
		}
		return false;
	}
};