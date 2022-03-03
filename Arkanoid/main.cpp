#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"

constexpr int num_max_bricks = 120;
constexpr int num_max_balls = 10;
constexpr int num_max_entities = num_max_bricks + num_max_balls + 1;


constexpr int screen_width = 640;
constexpr int screen_height = 480;

int main()
{
    InitWindow(screen_width, screen_height, "Arkanoid - David Bang");
    SetTargetFPS(60);


    int bricksPerRow = 10;
    int bricksPerColumn = 5;

    RenderComponent renderers[num_max_entities] = {};
    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    int rendererIndex = 0;

    int x;
    int y;
    for (int i = 0; i < num_max_bricks; i++)
    {
        x = i % bricksPerRow;
        y = i / bricksPerRow;
        rendererIndex = i;
        Brick& brick = bricks[i];
        brick.assignRenderer(renderers[rendererIndex]);
        brick.x = x * brick.width;
        brick.y = y * brick.height;
        brick.color = (x + y) % 2 == 0 ? GREEN : BLUE;
    }

    for (int i = 0; i < num_max_balls; i++)
    {
        Ball& ball = balls[i];
        ball.assignRenderer(renderers[++rendererIndex]);
        ball.x = 200 + (i * ball.width + i * 15);
        ball.y = 300;
        ball.color = YELLOW;
    }


    Player player{renderers[++rendererIndex]};

    //AABB a = AABB::make_from_position_size(400, 200, 40, 40);


    int ballIndex = 0;
    uint64_t time = 0;
    uint64_t prev_time = 0;
    float delta_time;

    float delay = 1;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        time = GetTime();
        delta_time = time - prev_time;

        delay -= delta_time;

        //if (IsKeyDown(KEY_SPACE) && delay <= 0)
        //{
        //    Ball& ball = balls[ballIndex];
        //    ball.setActive();
        //    ball.x = player.x;
        //    ball.y = player.y - ball.height;
        //    ++ballIndex %= num_max_balls;
        //    delay = 1;
        //}
        //if (IsKeyDown(KEY_RIGHT))
        //{
        //    player.x += 1;
        //}
        //if (IsKeyDown(KEY_LEFT))
        //{
        //    player.x -= 1;
        //}
  
        BeginDrawing();

        for (int i = 0; i < num_max_entities; i++)
        {
            if (renderers[i].isVisible)
            {
                renderers[i].update();
            }
        }


        prev_time = time;
        ClearBackground(BLACK);

        EndDrawing();
    }



    CloseWindow();


    return 0;
}