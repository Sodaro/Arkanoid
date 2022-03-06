#pragma once
#include "raylib.h"
#include "common.h"
#include <iostream>
struct PhysicsComponent
{
	CollisionComponent* collider;
	Vector2 velocity;
	vec2_ptr pos;
	bool isActive = false, reflectOnCollision = true;
	PhysicsComponent()
	{
		collider = nullptr;
		pos = nullptr;
		velocity = Vector2{ 0,0 };
		isActive = false;
	}
	PhysicsComponent(CollisionComponent& collider) : collider(&collider)
	{
		pos = nullptr;
		velocity = Vector2{ 0,0 };
		isActive = false;
	};

	void update(float dt)
	{

	
	    //reflection
		if (reflectOnCollision)
		{
			if (!step(velocity.x * dt, 0.f))
				velocity.x = -velocity.x * 1.2f;

			if (!step(0.f, velocity.y * dt))
				velocity.y = -velocity.y * 1.2f;
		}
		else
		{
			moveInsideScreen(velocity.x * dt, velocity.y * dt);
			collider->update();
		}
	
	    //separating step into y and x separately, we're the ball can slide up and down bricks instead of stopping
	}
	bool moveInsideScreen(float dx, float dy)
	{
		if (pos->x + dx < 0 || pos->x + dx >= 640 || pos->y + dy < 0 || pos->y + dy >= 480)
			return false;

		pos->x += dx;
		pos->y += dy;
		return true;
		
	}

	bool step(float dx, float dy)
	{
		if (!isActive || collider == nullptr)
			return false;

		Vector2 newPos;
		newPos.x = pos->x + dx;
		newPos.y = pos->y + dy;

		bool collision = collider->checkCollisions(newPos);
		if (collision)
			return false;

		return moveInsideScreen(dx, dy);
	}
};
