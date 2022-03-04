#pragma once
#include "entity.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "collision.h"

struct Brick
{
private:
	RenderComponent* renderer;
	CollisionComponent* collider;

	//CollisionComponent* collision;
public:
	int width = 64, height = 24;
	int x = 0, y = 0;
	Color color;
	Brick()
	{
		color = WHITE;
		renderer = nullptr; 
	};
	Brick(RenderComponent& renderer) : renderer(&renderer)
	{
		color = WHITE;
	};
	void assignRenderer(RenderComponent& renderer)
	{
		this->renderer = &renderer;
		renderer.isVisible = true;
		renderer.width = width;
		renderer.height = height;
		renderer.color = &color;
		renderer.x = &x;
		renderer.y = &y;
	}
	void assignCollider(CollisionComponent& collider)
	{
		this->collider = &collider;
	}

	// Inherited via Entity
	//void render() override;


};