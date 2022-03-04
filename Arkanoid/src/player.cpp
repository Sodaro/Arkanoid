#include "player.h"

void Player::update(float dt)
{
    shootDelay -= dt;
	if (Input::actionPressed() && shootDelay <= 0)
	{
        Ball& ball = balls[ballIndex];
        ball.setActive();
        ball.x = this->x;
        ball.y = this->y - ball.height;
        ++ballIndex %= nrOfBalls;
        shootDelay = 1;
	}
    int horizontal = Input::getHorizontalInput();
    Vector2 newVelocity;
    newVelocity.x = 200.f * horizontal;
    newVelocity.y = 0.f;
    physics->velocity = newVelocity;
        
}
