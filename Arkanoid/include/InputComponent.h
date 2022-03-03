#pragma once
#include "raylib.h"
class InputComponent
{
	bool actionPressed() { return (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ENTER)); };
	int getHorizontalInput() 
	{
		int horizontal = 0;
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
			horizontal -= 1;

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
			horizontal += 1;

		return horizontal;
	}
public:
	InputComponent()
	{
	
	}
	void update()
	{
		//if (actionPressed() && delay <= 0)
		//{
		//	Ball& ball = balls[ballIndex];
		//	ball.setActive();
		//	ball.x = player.x;
		//	ball.y = player.y - ball.height;
		//	++ballIndex %= num_max_balls;
		//	delay = 1;
		//}
	}
};
