#pragma once
#include "raylib.h"
#include "common.h"
struct PhysicsComponent
{
	Vector2 velocity;
	int_ptr x, y;
	bool isActive;
	PhysicsComponent()
	{
		x = y = nullptr;
		velocity = Vector2{ 0,0 };
		isActive = true;
	}

	virtual void update()
	{
	}
};
