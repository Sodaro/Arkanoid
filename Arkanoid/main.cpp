#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"
#include "input.h"

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

    Input input;
    RenderComponent renderers[num_max_entities] = {};
    CollisionComponent colliders[num_max_entities] = {};

    PhysicsComponent physicsComponents[num_max_balls + 1] = {};

    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    int entityIndex = 0, physicsIndex = 0; 

    int x;
    int y;
    for (int i = 0; i < num_max_bricks; i++)
    {
        x = i % bricksPerRow;
        y = i / bricksPerRow;
        entityIndex = i;
        Brick& brick = bricks[i];
        brick.assignRenderer(renderers[entityIndex]);
        brick.x = x * brick.width;
        brick.y = y * brick.height;
        brick.color = (x + y) % 2 == 0 ? GREEN : BLUE;
        CollisionComponent& collider = colliders[entityIndex];
        collider.init(&brick.x, &brick.y, &brick.width, &brick.height, colliders, num_max_entities);
    }

    for (int i = 0; i < num_max_balls; i++)
    {
        physicsIndex = i;
        Ball& ball = balls[i];
        PhysicsComponent& physics = physicsComponents[physicsIndex];
        entityIndex++;
        ball.assignRenderer(renderers[entityIndex]);
        ball.assignPhysics(physics);
        ball.x = 200 + (i * ball.width + i * 15);
        ball.y = 300;
        ball.color = YELLOW;
        CollisionComponent& collider = colliders[entityIndex];
        collider.init(&ball.x, &ball.y, &ball.width, &ball.height, colliders, num_max_entities);
        physics.collider = &collider;

    }

    Player player{num_max_balls};
    CollisionComponent& collider = colliders[num_max_entities-1];
    PhysicsComponent& physics = physicsComponents[++physicsIndex];
    RenderComponent& renderer = renderers[num_max_entities - 1];
    collider.init(&player.x, &player.y, &player.width, &player.height, colliders, num_max_entities);
    
    physics.collider = &collider;
    player.assignCollider(collider);
    player.assignPhysics(physics);
    player.assignRenderer(renderer);

    //AABB a = AABB::make_from_position_size(400, 200, 40, 40);


    int nrOfPhysicsObjects = sizeof(physicsComponents) / sizeof(PhysicsComponent);
    
    double time = 0;
    double prev_time = 0;
    float delta_time;

    float delay = 1;

    /*
    * balls:
    * initial velocity based on player move direction
    * go in one dir without velocity change
    * on collision:
    *   change velocity direction
    */



    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        time = GetTime();
        delta_time = (float)time - prev_time;

        delay -= delta_time;
        //input update
        //player update            GameObject update instead, and have player / enemies derive??
        //ai update
        //physics update
        //render update


        //if (IsKeyDown(KEY_RIGHT))
        //{
        //    player.x += 1;
        //}
        //if (IsKeyDown(KEY_LEFT))
        //{
        //    player.x -= 1;
        //}

        player.update(delta_time);

        for (int i = 0; i < nrOfPhysicsObjects; i++)
        {
            //add check for active objects
            physicsComponents[i].update(delta_time);
        }
            
  
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