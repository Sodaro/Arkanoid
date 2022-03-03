#pragma once
#include "raylib.h"
#include "common.h"
struct RenderComponent
{
	int width, height;
	Color* color;
	int_ptr x, y;
	bool isVisible;
	RenderComponent()
	{
		x = y = nullptr;
		width = 0, height = 0;
		isVisible = false;
		color = nullptr;
	}

	RenderComponent(int_ptr x, int_ptr y, int width, int height, Color* color)
	{
		isVisible = true;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->color = color;
	}
	//void SetColor(Color p_color)
	//{
	//	color = p_color;
	//}
	void update()
	{
		if (x != nullptr && y != nullptr && color != nullptr)
		{
			//DrawRectangleLines()
			DrawRectangleLines(*x, *y, width, height, *color);
		}
	}
};
