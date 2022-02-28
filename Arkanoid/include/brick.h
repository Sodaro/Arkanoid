#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

class Brick : Entity
{
	RenderComponent* renderer;
	CollisionComponent* collision;
public:

	// Inherited via Entity
	virtual void update() override;

	virtual void render() override;


};