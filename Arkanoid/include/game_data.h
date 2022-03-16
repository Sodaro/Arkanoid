#pragma once
#include <raylib.h>
#include <map>
#include <vector>
struct Data
{
	struct BrickData
	{
		char key = ' ';
		int health = 0;
		int score = 0;
		Color color1 = WHITE;
		Color color2 = WHITE;
		Color outline = WHITE;
	};
	struct PlayerData
	{
		Color color1 = WHITE;
		Color color2 = WHITE;
		Color outline = WHITE;
	};
	struct BallData
	{
		Color color1 = WHITE;
		Color color2 = WHITE;
		Color outline = WHITE;
	};
	std::map<char, BrickData> brickData;
	std::vector<char> keys;
	BallData ballData;
	PlayerData playerData;
};