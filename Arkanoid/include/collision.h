#pragma once
struct Circle
{
    float x;
    float y;
    float radius;
};

void draw_circle(const Circle& circle);

struct AABB
{
    int x_min, y_min, x_max, y_max;
    static AABB make_from_position_size(float x, float y, float w, float h);
    
};
void draw_box(const AABB& box);
bool aabb_intersect(const AABB& a, const AABB& b);
bool aabb_circle_intersect(const AABB& a, const Circle& b);



//TODO: IMPLEMENT COLLISION WITH DATA OR USE EXISTING