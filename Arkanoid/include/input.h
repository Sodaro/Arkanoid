#pragma once
class Input
{
public:
	static bool modeSwitchPressed();
	static bool actionPressed();
	static bool actionReleased();

	static int getVerticalInput();
	static int getHorizontalInput();
};
