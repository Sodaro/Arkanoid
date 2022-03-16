#include "player.h"
#include <iostream>
#include "physics_component.h"
#include "render_component.h"
#include "collision_component.h"

Player::Player(const int nrOfBalls) : nrOfBalls(nrOfBalls)
{
    pos = { game_width / 2,game_height - player_height - 10 };
    size = { player_width,player_height };
    color1 = color2 = MAGENTA;
    renderer = nullptr;
    collider = nullptr;
    physics = nullptr;
    balls = nullptr;
    ballShotCallback = nullptr;
}

Player::Player(RenderComponent* renderer, PhysicsComponent* physics, CollisionComponent* collider, Ball* ballsArr, const int nrOfBalls) : nrOfBalls(nrOfBalls)
{
    this->renderer = renderer;
    this->collider = collider;
    this->physics = physics;

    pos = { game_width / 2,game_height - player_height - 10 };
    size = { player_width,player_height };
    color1 = MAGENTA;
    this->renderer->isVisible = true;
    setupRenderer();
    balls = ballsArr;
    physics->pos = &pos;
    physics->size = size;
    physics->collider = collider;
    physics->isActive = true;
    physics->reflectOnCollision = false;
    ballShotCallback = nullptr;
}

void Player::setColor(Color c1, Color c2, Color o)
{
    color1 = c1;
    color2 = c2;
    outline = o;
    renderer->color1 = &this->color1;
    renderer->color2 = &this->color2;
    renderer->outline = &this->outline;
}

Player& Player::operator=(Player&& p) noexcept
{
    this->renderer = p.renderer;
    this->physics = p.physics;
    this->collider = p.collider;
    this->pos = p.pos;

    renderer->pos = &pos;
    physics->pos = &pos;
    collider->pos = &pos;

    this->size = p.size;
    this->balls = p.balls;

    p.renderer = nullptr;
    p.collider = nullptr;
    p.physics = nullptr;
    p.balls = nullptr;

    return *this;
}

void Player::update(float dt)
{
    //shootTimer -= dt;
	if (Input::actionPressed() && availableBalls > 0)
	{
        Ball& ball = balls[ballIndex];
        ball.setActive();
        ball.pos = pos;
        ball.pos.y -= ball.size.y + 5;
        ++ballIndex %= nrOfBalls;
        //shootTimer = shootDelay;

        if (ballShotCallback != nullptr)
            (game->*ballShotCallback)();

        availableBalls--;
	}
    int horizontal = Input::getHorizontalInput();
    Vector2 newVelocity;
    newVelocity.x = 200.f * horizontal;
    newVelocity.y = 0.f;
    physics->velocity = newVelocity;
        
}
