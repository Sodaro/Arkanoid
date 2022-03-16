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
		bool isBox;
		ColliderParams(CollisionComponent* p_colliders, const int p_numColliders) : colliders(p_colliders), numColliders(p_numColliders)
		{
			isBox = true;
			pos = size = nullptr;
			owner = nullptr;
		}
	};
	CollisionComponent* colliders = nullptr;
	int numColliders = 0;

	bool enabled = false;

	vec2_ptr pos = nullptr, size = nullptr;

	bool isBox = true;
	AABB box{ 0,0,0,0 };
	Circle circle{ 0,0,0 };
	void init(ColliderParams params);

	void updateBox();

	bool checkCollisions(Vector2 newPos);
};