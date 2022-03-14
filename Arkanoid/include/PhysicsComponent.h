#pragma once
#include "common.h"
struct CollisionComponent;
struct PhysicsComponent
{
	CollisionComponent* collider;
	Vector2 velocity, size;
	vec2_ptr pos;
	bool isActive = false, reflectOnCollision = true;
	PhysicsComponent();
	PhysicsComponent(CollisionComponent& collider);


	void update(double dt);
	bool moveInsideScreen(float dx, float dy);

	bool step(float dx, float dy);
};
