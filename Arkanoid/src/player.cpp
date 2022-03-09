#include "player.h"
#include <iostream>

void Player::update(float dt)
{
    shootTimer -= dt;
	if (Input::actionPressed() && shootTimer <= 0)
	{
        Ball& ball = balls[ballIndex];
        ball.setActive();
        ball.pos = pos;
        ball.pos.y -= ball.size.y + 5;
        ++ballIndex %= nrOfBalls;
        shootTimer = shootDelay;
	}
    int horizontal = Input::getHorizontalInput();
    Vector2 newVelocity;
    newVelocity.x = 200.f * horizontal;
    newVelocity.y = 0.f;
    physics->velocity = newVelocity;
        
}
