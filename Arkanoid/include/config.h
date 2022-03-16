#pragma once
constexpr int num_max_bricks = 42;
constexpr int num_max_balls = 10;
constexpr int num_max_entities = num_max_bricks + num_max_balls + 1;

constexpr int bricksPerRow = 7;
constexpr int bricksPerColumn = 6;

constexpr int game_width = 224;
constexpr int game_height = 256;

constexpr int brick_width = 32;
constexpr int brick_height = 14;

constexpr int player_width = 48;
constexpr int player_height = 14;

constexpr int ball_width = 8;
constexpr int ball_height = 8;

constexpr int screen_width = game_width*4;
constexpr int screen_height = game_height*4;