#include "game.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ui_helper.h"
#include "utilities.h"
#include "render_component.h"
#include "physics_component.h"
#include "collision_component.h"
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
    Utilities::fillWithLeadingZeroes(scoreText, 8);

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

bool Game::levelSelectUpdate()
{
    if (levelsFetched == false)
    {
        levels = Utilities::fetchLevels();
        levelsFetched = true;
    }
    
    int prevIndex = -1, nextIndex = -1;

    int levelCount = (int)levels.size();
    if (levelCount == 0 || WindowShouldClose())
    {
        levelsFetched = false;
        return false;
    }

    int verticalInput = Input::getVerticalInput();
    if (verticalInput != 0)
    {
        openSelectedIndex += verticalInput;
        if (openSelectedIndex >= levelCount)
            openSelectedIndex = 0;
        else if (openSelectedIndex < 0)
            openSelectedIndex = levelCount - 1;
    }

    if (levelCount >= 2)
    {
        nextIndex = (openSelectedIndex + 1) % levelCount;
    }
    if (levelCount >= 3)
    {
        prevIndex = openSelectedIndex - 1;
        if (prevIndex < 0)
            prevIndex = levelCount - 1;
    }
    int fontSize = 8;
    int offsetPerChar = 8;
    Vector2 playBtnPos = { game_width / 2, game_height / 2 - 50 };
    Vector2 editorBtnPos = { game_width / 2, game_height / 2 };
    Vector2 quitBtnPos = { game_width / 2, game_height / 2 + 50 };


    BeginTextureMode(targetTexture);

    ClearBackground(BLACK);
    if (prevIndex != -1)
    {
        UI::drawCenteredTextWithBox(levels[prevIndex], fontSize, playBtnPos, GRAY, GRAY);
    }

    UI::drawCenteredTextWithBox(levels[openSelectedIndex], fontSize, editorBtnPos, WHITE, WHITE);
    if (nextIndex != -1)
    {
        UI::drawCenteredTextWithBox(levels[nextIndex], fontSize, quitBtnPos, GRAY, GRAY);
    }

    DrawText("Enter/Space: play", 0, game_height - 20, 12, WHITE);
    DrawText("UP/DOWN: navigate", 0, game_height - 40, 12, WHITE);
    EndTextureMode();

    BeginDrawing();
    DrawTexturePro(targetTexture.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
    EndDrawing();

    if (Input::actionPressed())
    {
        fileName = levels[openSelectedIndex];
        state = State::Gameplay;
        levelsFetched = false;
        return false;
    }
    return true;
}

bool Game::setup()
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

    int brickOffsetX = (int)bricks[0].size.x / 2;
    int brickOffsetY = (int)bricks[0].size.y / 2;

    std::size_t pos{};
    std::string input;
    int levelIndex = 0;

    std::ifstream file(Utilities::levels_path + fileName);
    std::string line, content;
    int index = 0;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            content += line;
        }
    }
    else
    {
        return false;
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
        case '6': dataIndex = (int)Data::BrickType::Six;   break;
        case '5': dataIndex = (int)Data::BrickType::Five;  break;
        case '4': dataIndex = (int)Data::BrickType::Four;  break;
        case '3': dataIndex = (int)Data::BrickType::Three; break;
        case '2': dataIndex = (int)Data::BrickType::Two;   break;
        case '1': dataIndex = (int)Data::BrickType::One;   break;
        case '0': dataIndex = (int)Data::BrickType::None;  break;
        }

        Data::BrickData brickData = data->brickData[dataIndex];
        bricks[i].initializeTypeData((Data::BrickType)dataIndex, brickData.color1, brickData.color2, brickData.outline, brickData.score, brickData.health);
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

        params.pos = &ball.pos;
        params.size = &ball.size;
        params.owner = &ball;
        params.isBox = true;
        collider->init(params);

        ball.game = this;

        ball.color1  = data->ballData.color1;
        ball.color2  = data->ballData.color2;
        ball.outline = data->ballData.outline;

        ball.assignRenderer(renderer);

        ball.assignPhysics(physics);
        ball.assignCollider(collider);
        ball.ballIndex = i;
        ball.onBallLeftScreen = &Game::onBallLeftScreen;
    }

    score = 0;
    scoreText = "0";
    Utilities::fillWithLeadingZeroes(scoreText, 8);
    CollisionComponent* collider = &colliders[num_max_entities - 1];
    PhysicsComponent* physics = &physicsComponents[++physicsIndex];
    RenderComponent* renderer = &renderers[num_max_entities - 1];
    player = Player{ renderer, physics, collider, balls, num_max_balls };
    player.setColor(data->playerData.color1, data->playerData.color2, data->playerData.outline);
    player.ballShotCallback = &Game::onBallShot;

    player.game = this;

    params.pos = &player.pos;
    params.size = &player.size;
    params.owner = &player;
    params.isBox = true;
    collider->init(params);
    collider->enabled = true;
    return true;
}

void Game::reset()
{
    for (Ball& ball : balls)
        ball.disable();

    for (int i = 0; i < num_max_bricks; i++)
    {
        int y = i / bricksPerRow;
        Brick& brick = bricks[i];
        brick.resetHealth();
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
    std::string multipStr = "Multip:" + std::to_string(numActiveBalls) + "x";
    DrawText(livesStr.c_str(), 0, game_height - 50, 12, WHITE);
    DrawText(unlockStr.c_str(), 0, game_height - 20, 12, WHITE);

    DrawText(scoreText.c_str(), game_width - 100, game_height - 20, 12, WHITE);
    DrawText(multipStr.c_str(), game_width - 100, game_height - 50, 12, WHITE);

    if (isGameWon)
    {
        DrawText("You won!", game_width / 2 - 60, game_height / 2 - 40, 32, WHITE);
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
    state = State::LevelSelect;
    destroyWav = LoadSound("resources/brick_destroy.wav");
}

void Game::run()
{
    int renderMode = (int)RenderComponent::Mode::FILL_LINES;
    int nrOfPhysicsObjects = sizeof(physicsComponents) / sizeof(PhysicsComponent);

    Rectangle gradientRect = { 0,0,game_width, game_height };

    if (!setup())
        return;
    reset();

    double time = GetTime();
    double prev_time = time;
    double delta_time;

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

            //player logic update
            player.update((float)delta_time);

            //update everything that moves
            for (int i = 0; i < nrOfPhysicsObjects; i++)
            {
                if (physicsComponents[i].isActive)
                {
                    physicsComponents[i].update((float)delta_time);
                }
            }

            //check if balls have left screen
            for (int i = 0; i < num_max_balls; i++)
            {
                balls[i].handleOutsideScreen();
            }

            BeginTextureMode(targetTexture);

            ClearBackground(BLACK);
            DrawRectangleGradientV((int)gradientRect.x, (int)gradientRect.y, (int)gradientRect.width, (int)gradientRect.height, bg_two, bg_one);

            if (Input::modeSwitchPressed())
            {
                renderMode++;
                renderMode %= (int)RenderComponent::Mode::COUNT;
            }

            //render every active rendercomponent
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
