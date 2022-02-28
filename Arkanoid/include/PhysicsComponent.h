#pragma once
#include "raylib.h"
class PhysicsComponent
{
	Vector2 velocity;
public:
	bool isActive;
	PhysicsComponent()
	{
		velocity = Vector2{ 0,0 };
		isActive = true;
	}

	virtual void update()
	{
	}
};
