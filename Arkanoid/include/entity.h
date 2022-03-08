#pragma once
#include "raylib.h"
struct RenderComponent;
struct CollisionComponent;
struct PhysicsComponent;

class Entity
{
protected:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	CollisionComponent* collider;
	
	void setupRenderer();

public:
	Color color;
	Vector2 pos, size;

	Entity();
	Entity(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider);

	//virtual void onCollision(Entity* owner) = 0;
	//void assignCollisionCallback();
	virtual void onCollision(Vector2 normal) {};
	virtual void onLeaveScreen(Vector2 border) {};
	void assignRenderer(RenderComponent* renderer);
	void assignPhysics(PhysicsComponent* physics);
	void assignCollider(CollisionComponent* collider);

};

