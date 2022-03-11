#pragma once
#include "raylib.h"
class Input
{
public:
	static bool modeSwitchPressed();
	static bool actionPressed();

	static int getVerticalInput();
	static int getHorizontalInput();
};
