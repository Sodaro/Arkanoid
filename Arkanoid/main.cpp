#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"

constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

int main()
{
    Player player;
    Brick* bricks = new Brick[50];
    InitWindow(screenWidth, screenHeight, "Arkanoid - David Bang");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

  
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}