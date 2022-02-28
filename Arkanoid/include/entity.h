#pragma once
#include "raylib.h"

class Entity
{
	int width, height;
public:
	Vector2 position;
	virtual void update()=0;
	virtual void render()=0;
};