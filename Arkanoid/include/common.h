#pragma once
#include <raylib.h>

typedef Vector2* vec2_ptr;
typedef int* int_ptr;

class Entity;
class Game;

typedef void (Game::*action)();
typedef void (Game::*actionInt)(int);


struct CollisionParams
{
	Entity* colliderObject = nullptr;
	Vector2 contactPoint = Vector2{0,0};
	Vector2 normal = Vector2{ 0,0 };
};

constexpr Color bg_one = { 213,86,1,255 };
constexpr Color bg_two = { 25,5,7,255 };


enum class OP_CODE{SUCCESS, EXIT, APPLICATION_QUIT};