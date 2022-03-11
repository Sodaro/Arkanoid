#pragma once
constexpr int num_max_bricks = 42;
constexpr int num_max_balls = 10;
constexpr int num_max_entities = num_max_bricks + num_max_balls + 1;


constexpr int game_width = 224;
constexpr int game_height = 256;

constexpr int brick_width = 32;
constexpr int brick_height = 14;

constexpr int player_width = 48;
constexpr int player_height = 14;

constexpr int ball_width = 8;
constexpr int ball_height = 8;

constexpr int screen_width = game_width*2;
constexpr int screen_height = game_height*2;

constexpr int bricksPerRow = 7;
constexpr int bricksPerColumn = 6;





//SCORES { Green, Purple, Blue, Yellow, Red, Gray };
constexpr int brick_green_score = 50;
constexpr int brick_purple_score = 100;
constexpr int brick_blue_score = 150;
constexpr int brick_yellow_score = 200;
constexpr int brick_red_score = 250;
constexpr int brick_gray_score = 300;