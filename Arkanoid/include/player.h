#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"

class Player
{
	RenderComponent* renderer;
	//CollisionComponent* collision;
	//PhysicsComponent* physics;
	//InputComponent* input;

	int width = 128, height = 24;
	Color color;
public:
	int x = 256, y = 456;
	Player(RenderComponent& renderer)
	{
		color = MAGENTA;
		this->renderer = &renderer;
		renderer.isVisible = true;
		renderer.color = &color;
		renderer.x = &x;
		renderer.y = &y;
		renderer.width = width;
		renderer.height = height;
	}

	// Inherited via Entity
	void update();
	void render();


};