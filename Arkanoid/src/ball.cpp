#include "ball.h"
#include "collision.h"
//
void Ball::update()
{
    //REFACTOR THIS TO CORRECT PLACE AND COMPONENT ETC

    if (!alive)
        return;

    Circle circle = { x,y,4 };
    AABB box = AABB::make_from_position_size(brick.x, brick.y, brick.w, brick.h);

    if (aabb_circle_intersect(box, circle))
    {
        alive = false;
        return;
    }

    x += 400 * delta_time;
}
//
//void Ball::render()
//{
//}
