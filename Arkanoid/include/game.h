#pragma once
#include <vector>
#include <string>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"
#include "input.h"
#include "raymath.h"
#include "config.h"
#include "game_data.h"
#include "render_component.h"
#include "physics_component.h"
#include "collision_component.h"

class Game
{
    int openSelectedIndex = 0;

    std::vector<std::string> levels;
    Data* data;
    RenderTexture2D targetTexture;
    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    RenderComponent renderers[num_max_entities] = {};
    CollisionComponent colliders[num_max_entities] = {};
    PhysicsComponent physicsComponents[num_max_balls + 1] = {};
    Player player{ num_max_balls };
    std::string fileName;

    bool isRunning = true;
    bool gameOver = false;
    bool isGameWon = false;
    bool levelsFetched = false;

    int lives = 3;
    int numCreatedBricks = 0;
    int numActiveBalls = 0;
    int destroyedBrickCount = 0;

    uint16_t score = 0;
    std::string scoreText = "0";

    uint8_t bricksNeededForNextBall = 2;
    uint8_t bricksSinceLastBall = 0;

    Sound destroyWav;


    void drawUIText();

    void drawRenderTexture();

    void onBrickDestroyed(int index);

    void onBallLeftScreen(int index);

    void onBallShot();
    
    bool setup();
    
    void reset();

    public:
        enum class State { LevelSelect, Gameplay };
        State state;
        Game(RenderTexture2D& target, Data& data);
        bool levelSelectUpdate();
        void run();
};