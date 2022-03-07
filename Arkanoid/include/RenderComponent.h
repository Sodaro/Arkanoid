#pragma once
#include "raylib.h"
#include "common.h"
#include "raymath.h"
struct RenderComponent
{
	Color* color;
	vec2_ptr pos;
	Vector2 size;
	bool isVisible;
	RenderComponent()
	{
		pos = nullptr;
		size = Vector2{ 0,0 };
		isVisible = false;
		color = nullptr;
	}

	RenderComponent(vec2_ptr pos, Vector2 size, Color* color)
	{
		isVisible = true;
		this->pos = pos;
		this->size = size;
		this->color = color;
	}
	//void SetColor(Color p_color)
	//{
	//	color = p_color;
	//}
	void update()
	{
		if (pos != nullptr && color != nullptr)
		{
			//DrawRectangleLines()

			DrawRectangleLines(round(pos->x - size.x/2), round(pos->y - size.y/2), (int)size.x, (int)size.y, *color);
		}
	}
};
