#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"

class Player : public Entity
{
	RenderComponent* renderer;
	CollisionComponent* collision;
	PhysicsComponent* physics;
	InputComponent* input;
public:


	// Inherited via Entity
	virtual void update() override;


	virtual void render() override;


};