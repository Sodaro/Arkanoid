#include "common.h"
#include "raymath.h"
#include "RenderComponent.h"
//Color darken(Color& a, float amount)
//{
//	Color color;
//	color.r = Clamp(a.r - amount, 0, 255);
//	color.g = Clamp(a.g - amount, 0, 255);
//	color.b = Clamp(a.b - amount, 0, 255);
//	return color;
//}

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
		Rectangle rect = { round(pos->x - size.x / 2), round(pos->y - size.y / 2), size.x - 1, size.y - 1 };

		//DrawRectangleLines()
		switch (renderMode)
		{
		case RenderComponent::FILL:
			//DrawRectangle(rect.x, rect.y, (int)rect.width + 1, (int)rect.height + 1, multiplyColor(, gameColor));
			//DrawRectangleGradientEx(rect, multiplyColor(*color, color2), *color, *color, *color);
			DrawRectangleGradientV(rect.x, rect.y, rect.width, rect.height, *color1, *color2);
			break;
		case RenderComponent::FILL_LINES:
			//DrawRectangle(rect.x, rect.y, (int)rect.width, (int)rect.height, multiplyColor(*color, gameColor));
			//DrawRectangle(rect.x, rect.y, (int)rect.width, (int)rect.height, *color);
			//DrawRectangleGradientEx(rect, multiplyColor(*color, color2), *color, *color, *color);
			DrawRectangleGradientV(rect.x, rect.y, rect.width, rect.height, *color1, *color2);
			DrawRectangleLinesEx(rect, 2, *outline);
			break;
		case RenderComponent::LINES:
			//DrawRectangleLinesEx(rect, 3, multiplyColor(*color, gameColor));
			DrawRectangleLinesEx(rect, 2, *color1);
			break;
		default:
			break;
		}
	}
}