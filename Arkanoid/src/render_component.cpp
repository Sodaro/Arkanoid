#include "common.h"
#include "raymath.h"
#include "render_component.h"
RenderComponent::RenderComponent()
{
	pos = nullptr;
	size = Vector2{ 0,0 };
	isVisible = false;
	color1 = color2 = outline = nullptr;
}
RenderComponent::RenderComponent(vec2_ptr pos, Vector2 size, Color* color)
{
	isVisible = true;
	this->pos = pos;
	this->size = size;
	this->color1 = this->color2 = this->outline = color;
}
void RenderComponent::update(Mode renderMode)
{
	if (pos != nullptr && color1 != nullptr)
	{
		Rectangle rect = { roundf(pos->x - size.x / 2), roundf(pos->y - size.y / 2), size.x - 1, size.y - 1 };
		switch (renderMode)
		{
		case RenderComponent::Mode::FILL:
			DrawRectangleGradientV((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, *color1, *color2);
			break;
		case RenderComponent::Mode::FILL_LINES:
			DrawRectangleGradientV((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, *color1, *color2);
			DrawRectangleLinesEx(rect, 2, *outline);
			break;
		case RenderComponent::Mode::LINES:
			DrawRectangleLinesEx(rect, 2, *color1);
			break;
		default:
			break;
		}
	}
}