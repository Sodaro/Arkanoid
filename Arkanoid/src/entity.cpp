
#include "render_component.h"
#include "physics_component.h"
#include "collision_component.h"
#include "entity.h"
void Entity::setupRenderer()
{
	renderer->size = size;
	renderer->color1 = &color1;
	renderer->color2 = &color2;
	renderer->outline = &outline;
	renderer->pos = &pos;
}

Entity::Entity()
{
	renderer = nullptr;
	physics = nullptr;
	collider = nullptr;
	game = nullptr;
	color1 = color2 = outline = WHITE;
	pos = { 0,0 };
	size = { 0,0 };
}

Entity::Entity(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider) : renderer(renderer), physics(physics), collider(collider)
{
	game = nullptr;
	color1 = color2 = outline = WHITE;
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
	physics->size = size;
}

void Entity::assignCollider(CollisionComponent* collider)
{
	this->collider = collider;
	collider->owner = this;
}

void Entity::enable()
{
	if (collider != nullptr)
		collider->enabled = true;
	if (renderer != nullptr)
		renderer->isVisible = true;
	if (physics != nullptr)
		physics->isActive = true;
}

void Entity::disable()
{
	if (collider != nullptr)
		collider->enabled = false;
	if (renderer != nullptr)
		renderer->isVisible = false;
	if (physics != nullptr)
		physics->isActive = false;
}

Vector2 Entity::getVelocity()
{
	if (physics == nullptr)
		return Vector2{ 0, 0 };
	
	return physics->velocity;
}
