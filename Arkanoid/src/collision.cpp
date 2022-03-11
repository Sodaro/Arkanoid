#include "collision.h"
#include "raylib.h"
#include "raymath.h"
#include "common.h"



void draw_circle(const Circle& c)
{
	int resolution = 48;
	float step = (2 * PI) / resolution;

	for (int i = 0; i < resolution; ++i)
	{
		float angle = step * i;
		double x1 = cos(angle);
		double y1 = sin(angle);

		float next_angle = step * (i + 1);
		double x2 = cos(next_angle);
		double y2 = sin(next_angle);

		DrawLine(
			(int)(x1 * c.radius + c.x),
			(int)(y1 * c.radius + c.y),
			(int)(x2 * c.radius + c.x),
			(int)(y2 * c.radius + c.y),
			WHITE
		);
	}
}

bool circle_intersect(const Circle& a, const Circle& b, Vector2& normal)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;

	// Pythagoras!!!!
	// dist^2 = x^2 + y^2
	float dist_sqrd = dx * dx + dy * dy;
	double dist = sqrt(dist_sqrd);

	float radius_sum = a.radius + b.radius;
	if (dist < radius_sum)
	{
		if (fabs(dx) < fabs(dy))
			normal = Vector2{ dx < 0.f ? -1.f : 1.f, 0 };
		else
			normal = Vector2{ dx < 0.f ? -1.f : 1.f, 0 };
	}
	return dist < radius_sum;
}

bool line_intersect(const Vector2& line1, const Vector2& line2)
{
	return Vector2DotProduct(line1, line2) != 0;
}


//AABB AABB::make_from_position_size(int x, int y, int w, int h)
//{
//    AABB box;
//    box.x_min = x - w / 2;
//    box.y_min = y - h / 2;
//    box.x_max = x + w / 2;
//    box.y_max = x + w / 2;
//    return box;
//}

AABB AABB::make_from_position_size(vec2_ptr pos, vec2_ptr size)
{
	AABB box;
	box.x_min = pos->x - size->x / 2;
	box.y_min = pos->y - size->y / 2;
	box.x_max = pos->x + size->x / 2;
	box.y_max = pos->y + size->y / 2;
	return box;
}

AABB AABB::make_from_position_size2(int x1, int y1, int x2, int y2)
{
	AABB box;
	box.x_min = x1;
	box.x_max = x2;
	box.y_min = y1;
	box.y_max = y2;
	return box;
}

void draw_box(const AABB& box, Color color)
{
    Rectangle rect = 
    { 
        box.x_min, 
        box.y_min, 
		box.x_max - box.x_min,
		box.y_max - box.y_min
    };

    DrawRectangleLinesEx(rect, 1, color);
}
void draw_rect(const Rectangle rect)
{
	DrawRectangle(rect.x, rect.y, rect.width, rect.height, WHITE);
}

bool aabb_intersect(const AABB& a, const AABB& b)
{
	return
		(
			a.x_max > b.x_min &&
			b.x_max > a.x_min &&
			a.y_max > b.y_min &&
			b.y_max > a.y_min
			);
}
bool aabb_get_overlapping_area(const AABB& a, const AABB& b, Rectangle& rect)
{
	if (a.x_max > b.x_min &&
		b.x_max > a.x_min &&
		a.y_max > b.y_min &&
		b.y_max > a.y_min)
	{
		
		rect.x = fmaxf(a.x_min, b.x_min);
		rect.y = fmaxf(a.y_min, b.y_min);
		rect.width = fminf(a.x_max-a.x_min, b.x_max-b.x_min);
		rect.height = fminf(a.y_max-a.y_min, b.y_max-b.y_min);
		return true;
	}
	return false;
}

bool aabb_circle_intersect(const AABB& a, const Circle& b, Vector2& normal)
{
	float clamped_x = Clamp(b.x, a.x_min, a.x_max);
	float clamped_y = Clamp(b.y, a.y_min, a.y_max);

	float dx = b.x - clamped_x;
	float dy = b.y - clamped_y;

	float dist_squared = dx * dx + dy * dy;
	double dist = sqrt(dist_squared);

	if (dist < b.radius)
	{
		if (fabs(dx) < fabs(dy))
			normal = Vector2{ dx < 0.f ? -1.f : 1.f, 0 };
		else
			normal = Vector2{ dx < 0.f ? -1.f : 1.f, 0 };
	}

	return dist < b.radius;
}

Circle Circle::make_from_position_size(vec2_ptr pos, vec2_ptr size)
{
	Circle circle;
	circle.x = pos->x;
	circle.y = pos->y;
	circle.radius = size->x > size->y ? size->x : size->y;
	return circle;


	//TODO: FIX COLLISIONS
}
