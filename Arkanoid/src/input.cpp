#include "input.h"

bool Input::actionPressed() { return (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ENTER)); };
int Input::getHorizontalInput()
{
	int horizontal = 0;

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		horizontal += 1;

	if (IsKeyDown(KEY_A) ||IsKeyDown(KEY_LEFT))
		horizontal -= 1;

	return horizontal;
};