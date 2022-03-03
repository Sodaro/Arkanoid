#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"

class Ball
{
private:
	RenderComponent* renderer;
	//CollisionComponent* collision;
	//PhysicsComponent* physics;
	//InputComponent* input;


public:
	int width = 16, height = 16;
	Color color;
	int x = 0, y = 0;
	Ball()
	{
		color = WHITE;
		renderer = nullptr;
	};
	Ball(RenderComponent& renderer) : renderer(&renderer)
	{
		color = WHITE;
	};
	void setActive()
	{
		renderer->isVisible = true;
	}
	void assignRenderer(RenderComponent& renderer)
	{
		this->renderer = &renderer;
		renderer.isVisible = false;
		renderer.width = width;
		renderer.height = height;
		renderer.color = &color;
		renderer.x = &x;
		renderer.y = &y;
	}
};