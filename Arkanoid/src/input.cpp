#include "input.h"
#include "raylib.h"

bool Input::modeSwitchPressed()
{
	return IsKeyPressed(KEY_F1);
}

bool Input::actionPressed() { return (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)); };
bool Input::actionReleased() { return (IsKeyReleased(KEY_SPACE) || IsKeyReleased(KEY_ENTER)); };
int Input::getVerticalInput()
{
	int vertical = 0;

	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
		vertical -= 1;

	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
		vertical += 1;

	return vertical;
}
int Input::getHorizontalInput()
{
	int horizontal = 0;

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		horizontal += 1;

	if (IsKeyDown(KEY_A) ||IsKeyDown(KEY_LEFT))
		horizontal -= 1;

	return horizontal;
};