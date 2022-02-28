#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"

class Ball : public Entity
{
	RenderComponent* renderer;
	CollisionComponent* collision;
	PhysicsComponent* physics;
public:

	// Inherited via Entity
	virtual void update() override;

	virtual void render() override;
};