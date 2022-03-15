#pragma once
#include "common.h"
struct RenderComponent;
struct PhysicsComponent;
struct CollisionComponent;

class Entity
{
protected:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	CollisionComponent* collider;
	
	void setupRenderer();

public:
	Game* game;
	Color color1, color2, outline;
	Vector2 pos, size;

	Entity();
	Entity(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider);

	//virtual void onCollision(Entity* owner) = 0;
	//void assignCollisionCallback();
	virtual void onCollision(CollisionParams& params) {};
	virtual void onLeaveScreen(Vector2 border) {};
	void assignRenderer(RenderComponent* renderer);
	void assignPhysics(PhysicsComponent* physics);
	void assignCollider(CollisionComponent* collider);
	void enable();
	void disable();
	Vector2 getVelocity();
};

