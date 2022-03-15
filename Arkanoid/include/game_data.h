#pragma once
#include <raylib.h>
struct Data
{
	enum class BrickType { None, One, Two, Three, Four, Five, Six, Count };
	struct BrickData
	{
		int health = 0;
		int score = 0;
		Color color1;
		Color color2;
		Color outline;
	};
	struct PlayerData
	{
		Color color1;
		Color color2;
		Color outline;
	};
	struct BallData
	{
		Color color1;
		Color color2;
		Color outline;
	};
	BrickData brickData[(int)BrickType::Count];
	BallData ballData;
	PlayerData playerData;
};