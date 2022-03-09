#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"
#include "input.h"
#include "raymath.h"
#include "config.h"

float easeInQuart(float x) {
    return x * x * x * x;
}
float easeOutQuart(float x) {
    return 1 - pow(1 - x, 4);
}

Color lerpColor(Color& c1, Color& c2, float t)
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
Color easeInColor(Color& c1, Color& c2, float t)
{
    t = easeInQuart(t);
    unsigned char r = c1.r + t * (c2.r - c1.r);
    unsigned char g = c1.g + t * (c2.g - c1.g);
    unsigned char b = c1.b + t * (c2.b - c1.b);

    Color n;
    n.r = r;
    n.g = g;
    n.b = b;

    return n;
}
Color easeOutColor(Color& c1, Color& c2, float t)
{
    t = easeOutQuart(t);
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
    RenderComponent renderers[num_max_entities] = {};
    CollisionComponent colliders[num_max_entities] = {};
    PhysicsComponent physicsComponents[num_max_balls + 1] = {};
    
    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    Player player{ num_max_balls };

    Color bgColor{ 20,20,20,255 };

    Color(*ease)(Color&, Color&, float);

    int renderMode = 0;

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
                case 0: {brick.color = neon_gray;
                            brick.health = 2;} break;
                case 1: brick.color = neon_red;     break;
                case 2: brick.color = neon_yellow;  break;
                case 3: brick.color = neon_blue;    break;
                case 4: brick.color = neon_purple; break;
                case 5: brick.color = neon_green;   break; 
            }

            CollisionComponent* collider = &colliders[entityIndex];
            params.pos = &brick.pos;
            params.size = &brick.size;
            params.owner = &brick;
            params.isBox = true;
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
            params.isBox = true;
            collider->init(params);


            ball.color = ball_color;

            ball.assignRenderer(renderer);
            
            ball.assignPhysics(physics);
            ball.assignCollider(collider);
        }


        CollisionComponent* collider = &colliders[num_max_entities - 1];
        PhysicsComponent* physics = &physicsComponents[++physicsIndex];
        RenderComponent* renderer = &renderers[num_max_entities - 1];
        player = Player{ renderer, physics, collider, balls, num_max_balls };
        player.setColor(player_color);
        params.pos = &player.pos;
        params.size = &player.size;
        params.owner = &player;
        params.isBox = true;
        collider->init(params);
        collider->enabled = true;
        //renderer->color = &player.color;

    }
    

    int nrOfPhysicsObjects = sizeof(physicsComponents) / sizeof(PhysicsComponent);
    
    double time = 0;
    double prev_time = 0;
    double delta_time;

    const int nrOfColors = 2;
    Color currentColor, targetColor, prevColor;
    //Color colors[nrOfColors] = { neon_red, neon_orange, neon_yellow, neon_green, neon_blue, neon_purple};
    Color colors[nrOfColors] = { Color{100,100,100,255}, Color{255,255,255,255} };
    //Color gray{ 40,40,40,255 };
    currentColor = prevColor = colors[0];
    targetColor = colors[0];

    bool forwardLerping = true;
    float currentLerpTime = 0;
    float inDuration = 2.f;
    float outDuration = 2.f;
    float currentDuration = inDuration;
    int colorIndex = 0;

    RenderTexture2D target = LoadRenderTexture(game_width, game_height);
    BeginTextureMode(target);
    ClearBackground(BLACK);
    EndTextureMode();

    int gradientX = 0, gradientY = 0;
    ease = easeInColor;
    
    Rectangle gradientRect = { 0,0,game_width, game_height };
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        time = GetTime();
        delta_time = (time - prev_time);

        currentLerpTime += delta_time;
        if (currentLerpTime >= currentDuration)
        {
            currentLerpTime = 0;
            forwardLerping = !forwardLerping;
            if (forwardLerping)
            {
                currentDuration = inDuration;
                ease = easeInColor;
            }
            else
            {
                currentDuration = outDuration;
                ease = easeOutColor;
            }


            prevColor = targetColor;
            
            colorIndex++;
            colorIndex %= nrOfColors;
            targetColor = colors[colorIndex];

        }
        
        currentColor = ease(prevColor, targetColor, currentLerpTime / currentDuration);


        //player logic update
        player.update(delta_time);

        for (int i = 0; i < nrOfPhysicsObjects; i++)
        {
            if (physicsComponents[i].isActive)
            {

                physicsComponents[i].update(delta_time);
            }
        }


        if (Input::modeSwitchPressed())
        {
            renderMode++;
            renderMode %= RenderComponent::Mode::COUNT;
        }
        

        //gradientX += 4;
        //gradientY += 3;

        //if (gradientX >= game_width)
        //{
        //    gradientX = 0;
        //    gradientY = 0;
        //}


        

        BeginTextureMode(target);
        //ClearBackground(neon_orange);
        ClearBackground(BLACK);
        //ClearBackground(colors[0]);
        DrawRectangleGradientV(gradientRect.x, gradientRect.y, gradientRect.width, gradientRect.height, bg_two, bg_one);

        for (int i = 0; i < num_max_entities; i++)
        {
            if (renderers[i].isVisible)
            {
                renderers[i].update((RenderComponent::Mode)renderMode, currentColor);
            }
        }

        
        //for (int i = 0; i < num_max_entities; i++)
        //{
        //    if (renderers[i].isVisible)
        //    {
        //        renderers[i].update((RenderComponent::Mode)renderMode, bgColor);
        //    }
        //}
        //BeginBlendMode(BLEND_MULTIPLIED);
        //DrawRectangleRec(gradientRect, currentColor);
        //EndBlendMode();
        
        //AABB a = AABB::make_from_position_size2(100, 100, 300, 300);
        //AABB b = AABB::make_from_position_size2(0, 0, 300, 300);
        //Rectangle overlap;

        //if (aabb_get_overlapping_area(a, b, overlap))
        //{
        //    draw_rect(overlap);
        //}

        //
        //draw_box(a, BLUE);
        //draw_box(b, MAGENTA);

        EndTextureMode();



        

        BeginDrawing();        
        
        DrawTexturePro(target.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
        //DrawFPS(0, 0);

        prev_time = time;

        EndDrawing();


    }


    UnloadRenderTexture(target);
    CloseWindow();


    return 0;
}