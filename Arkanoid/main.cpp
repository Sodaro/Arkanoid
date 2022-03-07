#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"
#include "input.h"
#include "raymath.h"
#include "config.h"

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

    RenderComponent renderers[num_max_entities] = {};
    CollisionComponent colliders[num_max_entities] = {};
    PhysicsComponent physicsComponents[num_max_balls + 1] = {};
    
    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    Player player{ num_max_balls };

    {

        int entityIndex = 0, physicsIndex = 0;
        CollisionComponent::ColliderParams params{ colliders, num_max_entities };

        int brickOffsetX = bricks[0].size.x / 2;
        int brickOffsetY = bricks[0].size.y / 2;

        for (int i = 0; i < num_max_bricks; i++)
        {
            int x = i % bricksPerRow;
            int y = i / bricksPerRow;
            entityIndex = i;
            Brick& brick = bricks[i];
            RenderComponent* renderer = &renderers[entityIndex];
            brick.assignRenderer(renderer);
            brick.pos = Vector2{ x * brick.size.x + brickOffsetX, y * brick.size.y + brickOffsetY };
            switch (y)
            {
                case 0: {brick.color = GRAY;
                            brick.health = 2;} break;
                case 1: brick.color = RED;     break;
                case 2: brick.color = YELLOW;  break;
                case 3: brick.color = BLUE;    break;
                case 4: brick.color = MAGENTA; break;
                case 5: brick.color = GREEN;   break; 
            }

            CollisionComponent* collider = &colliders[entityIndex];
            params.pos = &brick.pos;
            params.size = &brick.size;
            params.owner = &brick;
            collider->init(params);
            brick.assignCollider(collider);
            renderer->isVisible = true;


            //TODO: DO NOT SEND PTR TO ALL BRICKS
            brick.brickIndex = entityIndex;
            brick.bricks = bricks;
            if (i >= 50)
            {
                collider->enabled = true;
            }
        }

        for (int i = 0; i < num_max_balls; i++)
        {
            physicsIndex = i;
            entityIndex++;
            CollisionComponent* collider = &colliders[entityIndex];
            PhysicsComponent* physics = &physicsComponents[physicsIndex];
            RenderComponent* renderer = &renderers[entityIndex];
            Ball& ball = balls[i];

            //ball = Ball{renderer, physics, collider };
            ball.pos = Vector2{ 200 + (i * ball.size.x + i * 15), 340 };

            params.pos = &ball.pos;
            params.size = &ball.size;
            params.owner = &ball;
            collider->init(params);


            ball.color = YELLOW;

            ball.assignRenderer(renderer);
            
            ball.assignPhysics(physics);
            ball.assignCollider(collider);
        }


        CollisionComponent* collider = &colliders[num_max_entities - 1];
        PhysicsComponent* physics = &physicsComponents[++physicsIndex];
        RenderComponent* renderer = &renderers[num_max_entities - 1];
        player = Player{ renderer, physics, collider, balls, num_max_balls };
        player.color = MAGENTA;
        params.pos = &player.pos;
        params.size = &player.size;
        params.owner = &player;
        collider->init(params);
        collider->enabled = true;
    }


    int nrOfPhysicsObjects = sizeof(physicsComponents) / sizeof(PhysicsComponent);
    
    double time = 0;
    double prev_time = 0;
    double delta_time;

    Color magenta{ 255,0,255,255 }, cyan{ 0,255,255,255 }, currentColor, targetColor, prevColor;
    Color colors[7] = { RED, ORANGE, YELLOW, GREEN, cyan, BLUE, PURPLE};
    currentColor = prevColor = cyan;
    targetColor = colors[0];

    bool forwardLerping = true;
    float currentLerpTime = 0;
    float lerpDuration = 2.f;
    int colorIndex = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        time = GetTime();
        delta_time = (time - prev_time);

        currentLerpTime += delta_time;
        if (currentLerpTime >= lerpDuration)
        {
            currentLerpTime = 0;
            forwardLerping = !forwardLerping;
            prevColor = targetColor;
            
            colorIndex++;
            colorIndex %= 7;
            targetColor = colors[colorIndex];
        }
        currentColor = lerpColor(prevColor, targetColor, currentLerpTime / lerpDuration);


        //player logic update
        player.update(delta_time);

        for (int i = 0; i < nrOfPhysicsObjects; i++)
        {
            if (physicsComponents[i].isActive)
            {
                physicsComponents[i].update(delta_time);
            }
        }

            
  
        BeginDrawing();

        ClearBackground(Color{0,0,40,255});
        for (int i = 0; i < num_max_entities; i++)
        {
            if (renderers[i].isVisible)
            {

                renderers[i].update();
            }
        }
        BeginBlendMode(BLEND_MULTIPLIED);
        DrawRectangle(0, 0, 640, 480, currentColor);
        EndBlendMode();

        prev_time = time;

        EndDrawing();
    }



    CloseWindow();


    return 0;
}