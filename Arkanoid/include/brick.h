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
	Vector2 size{64,28};
	Vector2 pos{0,0};
	Color color;
	Brick()
	{
		collider = nullptr;
		color = WHITE;
		renderer = nullptr; 
	};
	Brick(RenderComponent& renderer) : renderer(&renderer)
	{
		collider = nullptr;
		color = WHITE;
	};
	void assignRenderer(RenderComponent& renderer)
	{
		this->renderer = &renderer;
		renderer.isVisible = true;
		renderer.size = size;
		renderer.color = &color;
		renderer.pos = &pos;
	}
	void assignCollider(CollisionComponent& collider)
	{
		this->collider = &collider;
	}

	// Inherited via Entity
	//void render() override;


};