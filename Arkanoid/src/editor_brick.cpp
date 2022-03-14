#include "editor_brick.h"

void EditorBrick::changeType(BrickType type)
{
	this->type = type;
	switch (type)
	{
	case BrickType::Green:
		color = neon_green;
		break;
	case BrickType::Purple:
		color = neon_purple;
		break;
	case BrickType::Blue:
		color = neon_blue;
		break;
	case BrickType::Yellow:
		color = neon_yellow;
		break;
	case BrickType::Red:
		color = neon_red;
		break;
	case BrickType::Gray:
		color = neon_gray;
		break;
	case BrickType::None:
		color = Color{ 0,0,0,0 };
		break;
	default:
		break;
	}
}
