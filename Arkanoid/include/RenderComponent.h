#pragma once
#include "raylib.h"
class RenderComponent
{
	int width, height;
	Color color;
public:
	bool isVisible;
	RenderComponent()
	{
		isVisible = true;
		width = 60;
		height = 40;
		color = MAGENTA;
	}
	void SetColor(Color p_color)
	{
		color = p_color;
	}
	virtual void update()
	{
		//DrawRectangle(x, y, width, height, color);
	}
};
