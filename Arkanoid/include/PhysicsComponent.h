#pragma once
#include "raylib.h"
#include "common.h"
struct PhysicsComponent
{
	CollisionComponent* collider;
	//int componentIndex = 0;
	Vector2 velocity;
	int_ptr x, y;
	bool isActive = false, reflectOnCollision = true;
	PhysicsComponent()
	{
		x = y = nullptr;
		velocity = Vector2{ 0,0 };
		isActive = false;
	}
	PhysicsComponent(CollisionComponent& collider) : collider(&collider)
	{
		x = y = nullptr;
		velocity = Vector2{ 0,0 };
		isActive = false;
	};

	void update(float dt)
	{
	    if (!isActive)
	        return;
	
	    //reflection
		if (reflectOnCollision)
		{
			if (!step(velocity.x * dt, 0))
				velocity.x = -velocity.x * 1.2f;

			if (!step(0.f, velocity.y * dt))
				velocity.y = -velocity.y * 1.2f;
		}
		else
		{
			moveInsideScreen(velocity.x * dt, velocity.y * dt);
		}


	
	
	    //separating step into y and x separately, we're the ball can slide up and down bricks instead of stopping
	}
	void moveInsideScreen(float dx, float dy)
	{
		if ((int)x + dx < 0 || (int)x + dx >= 640 || (int)y + dy < 0 || (int)y + dy >= 480)
			return;

		x += (int)dx;
		y += (int)dy;
	}

	bool step(float dx, float dy)
	{
		if (!isActive || collider == nullptr)
			return false;

		bool collision = collider->checkCollisions();
		if (reflectOnCollision && collision)
			return true;

		moveInsideScreen(dx, dy);
		return false;
	}
};
