#include "player.h"
#include <iostream>

void Player::update(float dt)
{
    shootDelay -= dt;
	if (Input::actionPressed() && shootDelay <= 0)
	{
        Ball& ball = balls[ballIndex];
        ball.setActive();
        ball.pos = pos;
        ball.pos.y -= ball.size.y + 50;
        ++ballIndex %= nrOfBalls;
        shootDelay = 1;
	}
    int horizontal = Input::getHorizontalInput();
    Vector2 newVelocity;
    newVelocity.x = 200.f * horizontal;
    newVelocity.y = 0.f;
    physics->velocity = newVelocity;
        
}
