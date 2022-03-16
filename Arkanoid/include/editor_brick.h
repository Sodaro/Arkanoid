#pragma once
#include "common.h"
#include "config.h"
#include "raylib.h"
#include "game_data.h"

struct RenderComponent;

struct EditorBrick
{
    RenderComponent* renderer;
    Data::BrickType type = (Data::BrickType)0;
    int typeIndex = 0;
    Vector2 size = { brick_width, brick_height };
    Vector2 pos = { 0,0 };
    Color color1 = WHITE, color2 = WHITE, outline = WHITE;
    void changeTypeAndColor(Data::BrickType type, Color c1, Color c2, Color o);
};