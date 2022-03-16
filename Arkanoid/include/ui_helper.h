#pragma once
#include <string>
struct Vector2;
struct Color;
namespace UI
{
    void drawTextCentered(std::string& text, int fontSize, Vector2 pos, Color textColor);
    void drawCenteredTextWithBox(std::string& text, int fontSize, Vector2 pos, Color boxColor, Color textColor);
    void drawCursor(Vector2 pos, Color color);
}