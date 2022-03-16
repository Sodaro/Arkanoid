#include "editor_brick.h"

void EditorBrick::changeTypeAndColor(char key, Color c1, Color c2, Color o)
{
	//this->type = type;
	this->key = key;
	color1 = c1;
	color2 = c2;
	outline = o;
}
