#pragma once
#include "common.h"
#include "config.h"
#include "raylib.h"
#include "RenderComponent.h"
struct EditorBrick
{
    RenderComponent* renderer;
    BrickType type;
    int typeIndex = 0;
    Vector2 size = { brick_width, brick_height };
    Vector2 pos = { 0,0 };
    Color color;
    void changeType(BrickType type);
};