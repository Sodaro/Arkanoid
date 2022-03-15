#include "game.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "entity_data.h"
void Game::onBrickDestroyed(int index)
{
    destroyedBrickCount++;
    bricksSinceLastBall++;
    if (bricksSinceLastBall >= bricksNeededForNextBall)
    {
        bricksNeededForNextBall <<= 1;
        player.availableBalls++;
        bricksSinceLastBall = 0;
    }


    score += bricks[index].score * numActiveBalls;
    scoreText = std::to_string(score);
    fillWithLeadingZeroes(scoreText, 8);

    float pitch = GetRandomValue(8, 12) / (float)10;

    SetSoundPitch(destroyWav, pitch);
    PlaySound(destroyWav);

    if (destroyedBrickCount >= numCreatedBricks)
        isGameWon = true;
}

void Game::onBallLeftScreen(int index)
{
    numActiveBalls--;
    if (bricksNeededForNextBall > 2)
        bricksNeededForNextBall >>= 1;

    bricksSinceLastBall = 0;
    if (numActiveBalls <= 0)
    {
        lives--;
        player.availableBalls++;
    }
}

void Game::onBallShot()
{
    numActiveBalls++;
}

void Game::setup()
{

    isRunning = true;
    gameOver = false;
    isGameWon = false;

    numActiveBalls = 0;
    destroyedBrickCount = 0;
    numCreatedBricks = 0;

    score = 0;
    scoreText = "0";
    int entityIndex = 0, physicsIndex = 0;
    CollisionComponent::ColliderParams params{ colliders, num_max_entities };

    int brickOffsetX = bricks[0].size.x / 2;
    int brickOffsetY = bricks[0].size.y / 2;

    std::ifstream file("level.txt");
    std::string line, content;
    int index = 0;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            content += line;
        }
    }

    for (int i = 0; i < num_max_bricks; i++)
    {
        int x = i % bricksPerRow;
        int y = i / bricksPerRow;
        entityIndex = i;
        Brick& brick = bricks[i];
        RenderComponent* renderer = &renderers[entityIndex];
        brick.assignRenderer(renderer);
        brick.pos = Vector2{ x * brick.size.x + brickOffsetX, y * brick.size.y + brickOffsetY };
        int dataIndex = 0;
        //Data::BrickData data = Data::brickData[0].color1, Data::brickData[0].color2, Data::brickData[0].score

        switch (content[i])
        {
        case 'G': dataIndex = (int)Data::BrickType::Six;   break;
        case 'y': dataIndex = (int)Data::BrickType::Four;  break;
        case 'r': dataIndex = (int)Data::BrickType::Five;  break;
        case 'p': dataIndex = (int)Data::BrickType::Two;   break;
        case 'b': dataIndex = (int)Data::BrickType::Three; break;
        case 'g': dataIndex = (int)Data::BrickType::One;   break;
        case 'n': dataIndex = (int)Data::BrickType::None;  break;
        }  
        bricks[i].initializeTypeData((Data::BrickType)dataIndex, data->brickData[dataIndex].color1, data->brickData[dataIndex].color2, data->brickData[dataIndex].score);
        brick.onDestroyCallback = &Game::onBrickDestroyed;


        CollisionComponent* collider = &colliders[entityIndex];
        params.pos = &brick.pos;
        params.size = &brick.size;
        params.owner = &brick;
        params.isBox = true;
        collider->init(params);
        brick.assignCollider(collider);
        renderer->isVisible = true;

        if (bricks[i].type == Data::BrickType::None)
            bricks[i].disable();
        else
            numCreatedBricks++;

        brick.game = this;
        brick.brickIndex = entityIndex;
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

        params.pos = &ball.pos;
        params.size = &ball.size;
        params.owner = &ball;
        params.isBox = true;
        collider->init(params);

        ball.game = this;

        ball.color1 = ball_color;

        ball.assignRenderer(renderer);

        ball.assignPhysics(physics);
        ball.assignCollider(collider);
        ball.ballIndex = i;
        ball.onBallLeftScreen = &Game::onBallLeftScreen;
    }

    score = 0;
    scoreText = "0";
    fillWithLeadingZeroes(scoreText, 8);
    CollisionComponent* collider = &colliders[num_max_entities - 1];
    PhysicsComponent* physics = &physicsComponents[++physicsIndex];
    RenderComponent* renderer = &renderers[num_max_entities - 1];
    player = Player{ renderer, physics, collider, balls, num_max_balls };
    player.setColor(player_color);
    player.ballShotCallback = &Game::onBallShot;

    player.game = this;

    params.pos = &player.pos;
    params.size = &player.size;
    params.owner = &player;
    params.isBox = true;
    collider->init(params);
    collider->enabled = true;
}

void Game::reset()
{
    for (Ball& ball : balls)
        ball.disable();

    for (int i = 0; i < num_max_bricks; i++)
    {
        int y = i / bricksPerRow;
        Brick& brick = bricks[i];
        if (y == 0)
            brick.health = 2;
        else
            brick.health = 1;

        if (brick.type != Data::BrickType::None)
            brick.enable();
    }

    player.availableBalls = 1;
    lives = 3;
    isGameWon = false;
    destroyedBrickCount = 0;
    bricksSinceLastBall = 0;
    bricksNeededForNextBall = 2;

}
void Game::drawUIText()
{
    std::string livesStr = "Lives: " + std::to_string(lives);
    std::string unlockStr = "New Ball in: " + std::to_string(bricksNeededForNextBall - bricksSinceLastBall);

    DrawText(livesStr.c_str(), 0, game_height - 50, 16, WHITE);
    DrawText(unlockStr.c_str(), 0, game_height - 20, 16, WHITE);
    DrawText(scoreText.c_str(), game_width - 100, game_height - 20, 16, WHITE);

    if (isGameWon)
    {
        DrawText("You won!", game_width / 2 - (8 * 5), game_height / 2, 16, WHITE);
    }
}

void Game::drawRenderTexture()
{
    BeginDrawing();
    DrawTexturePro(targetTexture.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
    EndDrawing();
}

Game::Game(RenderTexture2D& target, Data& data)
{
    this->targetTexture = target;
    this->data = &data;
    destroyWav = LoadSound("resources/brick_destroy.wav");
}

void Game::run()
{
    Color (Game::*ease)(Color&, Color&, float);

    int renderMode = 0;
    int nrOfPhysicsObjects = sizeof(physicsComponents) / sizeof(PhysicsComponent);

    double time = GetTime();
    double prev_time = time;
    double delta_time;

    const int nrOfColors = 2;
    Color currentColor, targetColor, prevColor;
    Color colors[nrOfColors] = { Color{100,100,100,255}, Color{255,255,255,255} };

    currentColor = prevColor = colors[0];
    targetColor = colors[0];

    bool forwardLerping = true;
    float currentLerpTime = 0;
    float inDuration = 2.f;
    float outDuration = 2.f;
    float currentDuration = inDuration;
    int colorIndex = 0;

    int gradientX = 0, gradientY = 0;
    ease = &Game::easeInColor;

    Rectangle gradientRect = { 0,0,game_width, game_height };

    setup();
    reset();

    while (isRunning == true)// Detect window close button or ESC key
    {
        if (gameOver)
        {
            reset();
            gameOver = false;
        }
        while (gameOver == false && isRunning == true)
        {
            time = GetTime();
            delta_time = (time - prev_time);
            

            currentLerpTime += delta_time;

            //player logic update
            player.update(delta_time);

            for (int i = 0; i < nrOfPhysicsObjects; i++)
            {
                if (physicsComponents[i].isActive)
                {
                    physicsComponents[i].update(delta_time);
                }
            }

            for (int i = 0; i < num_max_balls; i++)
            {
                balls[i].handleOutsideScreen();
            }

            BeginTextureMode(targetTexture);

            ClearBackground(BLACK);
            DrawRectangleGradientV(gradientRect.x, gradientRect.y, gradientRect.width, gradientRect.height, bg_two, bg_one);

            if (Input::modeSwitchPressed())
            {
                renderMode++;
                renderMode %= RenderComponent::Mode::COUNT;
            }
            for (int i = 0; i < num_max_entities; i++)
            {
                if (renderers[i].isVisible)
                {
                    renderers[i].update((RenderComponent::Mode)renderMode);
                }
            }

            drawUIText();
            EndTextureMode();

            drawRenderTexture();

            prev_time = time;

            isRunning = !WindowShouldClose();
            gameOver = lives <= 0;
        }
    }
}
