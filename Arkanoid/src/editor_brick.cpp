#include "editor_brick.h"

void EditorBrick::changeTypeAndColor(Data::BrickType type, Color c1, Color c2, Color o)
{
	this->type = type;
	color1 = c1;
	color2 = c2;
	outline = o;
}
