#pragma once
#include <raylib.h>

typedef Vector2* vec2_ptr;
typedef int* int_ptr;

class Entity;
class Game;
//class Ball;
//class Brick;
//class Player;
//typedef void (*action);
//typedef void (*actionInt)(int amount);

//typedef void (Brick::*brickAction)();
//typedef void (Brick::*brickActionInt)(int);
//
//typedef void (Player::*playerAction)();

typedef void (Game::*action)();
typedef void (Game::*actionInt)(int);


struct CollisionParams
{
	Entity* colliderObject = nullptr;
	Vector2 contactPoint = Vector2{0,0};
	Vector2 normal = Vector2{ 0,0 };
};

enum class BrickType { Green, Purple, Blue, Yellow, Red, Gray, None, Count };

constexpr Color neon_gray = { 229, 229, 229,255 };
constexpr Color neon_blue = { 42,255,255,255 };
constexpr Color neon_yellow = { 255,255,68,255 };
constexpr Color neon_orange = { 255,173,0,255 };
constexpr Color neon_red = { 255,78,96,255 };
constexpr Color neon_green = { 136,255,88,255 };
constexpr Color neon_purple = { 255,124,255,255 };
constexpr Color neon_pink = { 255,0,255,255 };

constexpr Color player_color = { 22,140,140,255 };
constexpr Color ball_color = { 21,40,82,255 };
constexpr Color bg_one = { 213,86,1,255 };
constexpr Color bg_two = { 25,5,7,255 };