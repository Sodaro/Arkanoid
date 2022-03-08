#include "entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"

void Entity::setupRenderer()
{
	renderer->size = size;
	renderer->color = &color;
	renderer->pos = &pos;
}

Entity::Entity()
{
	renderer = nullptr;
	physics = nullptr;
	collider = nullptr;
	color = WHITE;
	pos = { 0,0 };
	size = { 0,0 };
}

Entity::Entity(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider) : renderer(renderer), physics(physics), collider(collider)
{
	color = WHITE;
	color = WHITE;
	pos = { 0,0 };
	size = { 0,0 };
	if (renderer != nullptr)
	{
		renderer->isVisible = true;
		setupRenderer();
	}
	if (physics != nullptr)
	{
		physics->pos = &pos;
	}

	collider->owner = this;
}

//void Entity::assignCollisionCallback()
//{
//	collider->collisionCallback = collisionCallback;
//}

void Entity::assignRenderer(RenderComponent* renderer)
{
	this->renderer = renderer;
	renderer->isVisible = false;
	setupRenderer();
}

void Entity::assignPhysics(PhysicsComponent* physics)
{
	this->physics = physics;
	physics->pos = &pos;
}

void Entity::assignCollider(CollisionComponent* collider)
{
	this->collider = collider;
	collider->owner = this;
}