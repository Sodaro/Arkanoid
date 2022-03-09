#pragma once
#include "raylib.h"
#include "common.h"
struct Circle
{
    float x;
    float y;
    float radius;
    static Circle make_from_position_size(vec2_ptr pos, vec2_ptr size);
};

void draw_circle(const Circle& circle);

struct AABB
{
    float x_min, y_min, x_max, y_max;
    //static AABB make_from_position_size(int x, int y, int w, int h);
    static AABB make_from_position_size(vec2_ptr pos, vec2_ptr size);
    static AABB make_from_position_size2(int x1, int y1, int x2, int y2);
};
void draw_box(const AABB& box, Color color);
void draw_rect(const Rectangle rect);
bool aabb_intersect(const AABB& a, const AABB& b);
bool aabb_get_overlapping_area(const AABB& a, const AABB& b, Rectangle& rect);
bool aabb_circle_intersect(const AABB& a, const Circle& b, Vector2& normal);
bool circle_intersect(const Circle& a, const Circle& b, Vector2& normal);
//bool aabb_line_intersect(const AABB& a, const Vector2& line);
bool line_intersect(const Vector2& line1, const Vector2& line2);