#pragma once
#include "common.h"

struct RenderComponent
{
	Color* color1, *color2;
	vec2_ptr pos;
	Vector2 size;
	bool isVisible;
	enum Mode{LINES,FILL,FILL_LINES, COUNT};
	RenderComponent();
	RenderComponent(vec2_ptr pos, Vector2 size, Color* color);
	//void SetColor(Color p_color)
	//{
	//	color = p_color;
	//}
	void update(Mode renderMode);
};
