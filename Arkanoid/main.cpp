#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"
#include "input.h"
#include "raymath.h"

constexpr int num_max_bricks = 120;
constexpr int num_max_balls = 10;
constexpr int num_max_entities = num_max_bricks + num_max_balls + 1;


constexpr int screen_width = 640;
constexpr int screen_height = 480;


Color lerpColor(Color c1, Color c2, float t)
{
    unsigned char r = c1.r + t * (c2.r - c1.r);
    unsigned char g = c1.g + t * (c2.g - c1.g);
    unsigned char b = c1.b + t * (c2.b - c1.b);

    Color n;
    n.r = r;
    n.g = g;
    n.b = b;

    return n;
}

int main()
{
    InitWindow(screen_width, screen_height, "Arkanoid - David Bang");
    SetTargetFPS(60);



    /*TODO: Store index for components / register somehow
    * use the index info to reduce health on correct brick when hit
    */


    RenderComponent renderers[num_max_entities] = {};
    CollisionComponent colliders[num_max_entities] = {};
    PhysicsComponent physicsComponents[num_max_balls + 1] = {};
    
    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    Player player{ num_max_balls };

    {
        int bricksPerRow = 10;
        int bricksPerColumn = 5;
        int entityIndex = 0, physicsIndex = 0;
        CollisionComponent::ColliderParams params{ colliders, num_max_entities };

        for (int i = 0; i < num_max_bricks; i++)
        {
            int x = i % bricksPerRow;
            int y = i / bricksPerRow;
            entityIndex = i;
            Brick& brick = bricks[i];
            brick.assignRenderer(renderers[entityIndex]);
            brick.pos = Vector2{ x * brick.size.x, y * brick.size.y };
            brick.color = (x + y) % 2 == 0 ? GREEN : BLUE;
            CollisionComponent& collider = colliders[entityIndex];
            params.pos = &brick.pos;
            params.size = &brick.size;
            collider.init(params);
        }

        for (int i = 0; i < num_max_balls; i++)
        {
            physicsIndex = i;
            entityIndex++;
            CollisionComponent& collider = colliders[entityIndex];
            PhysicsComponent& physics = physicsComponents[physicsIndex];
            RenderComponent& renderer = renderers[entityIndex];
            Ball& ball = balls[i];

            //ball = Ball{renderer, physics, collider };
            ball.pos = Vector2{ 200 + (i * ball.size.x + i * 15), 340 };

            params.pos = &ball.pos;
            params.size = &ball.size;
            collider.init(params);


            ball.color = YELLOW;

            ball.assignRenderer(renderer);
            ball.assignPhysics(physics);
            ball.assignCollider(collider);
        }


        CollisionComponent& collider = colliders[num_max_entities - 1];
        PhysicsComponent& physics = physicsComponents[++physicsIndex];
        RenderComponent& renderer = renderers[num_max_entities - 1];
        player = Player{ renderer, physics, collider, balls, num_max_balls };
        params.pos = &player.pos;
        params.size = &player.size;
        collider.init(params);
    }


    int nrOfPhysicsObjects = sizeof(physicsComponents) / sizeof(PhysicsComponent);
    
    double time = 0;
    double prev_time = 0;
    float delta_time;

    float delay = 1;

    Color magenta{ 40,0,40,255 }, cyan{ 0,40,40,255 }, currentColor, targetColor, prevColor;

    currentColor = prevColor = cyan;
    targetColor = magenta;

    bool forwardLerping = true;
    float currentLerpTime = 0;
    float lerpDuration = 5.f;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        time = GetTime();
        delta_time = (float)(time - prev_time);

        delay -= delta_time;


        

        currentLerpTime += delta_time;
        if (currentLerpTime >= lerpDuration)
        {
            currentLerpTime = 0;
            forwardLerping = !forwardLerping;
            prevColor = targetColor;
            targetColor = forwardLerping ? magenta : cyan;
        }
        currentColor = lerpColor(prevColor, targetColor, currentLerpTime / lerpDuration);


        
        //input update
        //player update            GameObject update instead, and have player / enemies derive??
        //ai update
        //physics update
        //render update
        player.update(delta_time);

        for (int i = 0; i < nrOfPhysicsObjects; i++)
        {
            //add check for active objects
            if (physicsComponents[i].isActive)
            {
                physicsComponents[i].update(delta_time);
            }
        }
            
  
        BeginDrawing();
        ClearBackground(currentColor);

        draw_box(player.collider->box);
        for (int i = 0; i < num_max_entities; i++)
        {
            if (renderers[i].isVisible)
            {
                renderers[i].update();
            }
        }


        prev_time = time;

        EndDrawing();
    }



    CloseWindow();


    return 0;
}