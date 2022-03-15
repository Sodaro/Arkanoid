#pragma once
#include <raylib.h>
struct Data
{
	enum class BrickType { One, Two, Three, Four, Five, Six, None, Count };
	struct BrickData
	{
		int health = 0;
		int score = 0;
		Color color1;
		Color color2;
	};
	struct PlayerData
	{
		Color color1;
		Color color2;
	};
	struct BallData
	{
		Color color1;
		Color color2;
	};
	BrickData brickData[(int)BrickType::Count];
	BallData ballData;
	PlayerData playerData;
};