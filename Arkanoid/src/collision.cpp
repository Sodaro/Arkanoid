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

bool circle_intersect(const Circle& a, const Circle& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;

	// Pythagoras!!!!
	// dist^2 = x^2 + y^2
	float dist_sqrd = dx * dx + dy * dy;
	double dist = sqrt(dist_sqrd);

	float radius_sum = a.radius + b.radius;
	return dist < radius_sum;
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

void draw_box(const AABB& box)
{
    Rectangle rect = 
    { 
        box.x_min, 
        box.y_min, 
        box.x_max - box.x_min, 
        box.y_max - box.y_min
    };

    DrawRectangleLinesEx(rect, 1, WHITE);
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

bool aabb_circle_intersect(const AABB& a, const Circle& b)
{
	float clamped_x = Clamp(b.x, a.x_min, a.x_max);
	float clamped_y = Clamp(b.y, a.y_min, a.y_max);

	float dx = b.x - clamped_x;
	float dy = b.y - clamped_y;

	float dist_squared = dx * dx + dy * dy;
	double dist = sqrt(dist_squared);

	return dist < b.radius;
}
