#pragma once
#include "common.h"
#include "collision.h"

class Entity;

struct CollisionComponent
{
	Entity* owner;
	struct ColliderParams
	{
		Entity* owner;
		vec2_ptr pos, size;
		CollisionComponent* colliders;
		int numColliders;
		ColliderParams(CollisionComponent* p_colliders, const int p_numColliders) : colliders(p_colliders), numColliders(p_numColliders)
		{
			pos = size = nullptr;
			owner = nullptr;
		}
	};



	CollisionComponent* colliders = nullptr;
	int numColliders = 0;

	bool enabled = false;

	vec2_ptr pos = nullptr, size = nullptr;

	AABB box{ 0,0,0,0 };
	void init(ColliderParams params);

	void update();

	bool checkCollisions(Vector2 newPos);
};