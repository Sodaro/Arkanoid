#pragma once
#include "common.h"
#include "collision.h"

struct CollisionComponent
{
	CollisionComponent* colliders;
	int numColliders;

	bool enabled = false;

	int_ptr x, y, w, h;

	AABB box{0,0,0,0};
	void init(int_ptr x, int_ptr y, int_ptr w, int_ptr h, CollisionComponent* colliders, const int numColliders)
	{
		this->colliders = colliders;
		box = AABB::make_from_position_size(*x, *y, *w, *h);
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->numColliders = numColliders;
		enabled = true;
	}

	bool checkCollisions()
	{
		if (!enabled)
			return false;

		box = AABB::make_from_position_size(*x, *y, *w, *h);
		for (int i = 0; i < numColliders; ++i)
		{
			if (this == &colliders[i])
				continue;

			CollisionComponent collider2 = colliders[i];

			if (!collider2.enabled)
				continue;


			AABB box2 = collider2.box;
			if (aabb_intersect(box, box2))
				return false;
		}
	}
};