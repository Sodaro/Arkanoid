#pragma once
#include "common.h"

struct RenderComponent
{
	Color* color1, *color2, *outline;
	vec2_ptr pos;
	Vector2 size;
	bool isVisible;
	enum class Mode{LINES,FILL,FILL_LINES, COUNT};
	RenderComponent();
	RenderComponent(vec2_ptr pos, Vector2 size, Color* color);
	void update(Mode renderMode);
};
