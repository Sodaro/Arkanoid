#include "ui_helper.h"
#include <raylib.h>


void UI::drawTextCentered(std::string& text, int fontSize, Vector2 pos, Color textColor)
{
    int width = MeasureText(text.c_str(), fontSize);
    int mid = width / 2;
    DrawText(text.c_str(), pos.x - mid, pos.y, fontSize, textColor);
}
void UI::drawCenteredTextWithBox(std::string& text, int fontSize, Vector2 pos, Color boxColor, Color textColor)
{
    DrawRectangleLines(pos.x - 80, pos.y - 5, 160, 25, boxColor);
    UI::drawTextCentered(text, fontSize, pos, textColor);
}

void UI::drawCursor(Vector2 pos, Color color)
{
    float radius = 2.f;
    DrawCircle(pos.x - radius/2, pos.y - radius/2, radius, color);
}
