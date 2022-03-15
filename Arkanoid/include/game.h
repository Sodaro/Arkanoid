#pragma once
#include <iostream>
#include "raylib.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "collision.h"
#include "input.h"
#include "raymath.h"
#include "config.h"
#include <string>
#include "game_data.h"
#include <vector>

class Game
{
    std::vector<std::string> levels;
    Data* data;
    RenderTexture2D targetTexture;
    Brick bricks[num_max_bricks];
    Ball balls[num_max_balls];
    RenderComponent renderers[num_max_entities] = {};
    CollisionComponent colliders[num_max_entities] = {};
    PhysicsComponent physicsComponents[num_max_balls + 1] = {};
    Player player{ num_max_balls };
    

    bool isRunning = true;
    bool gameOver = false;
    bool isGameWon = false;


    int lives = 3;
    int numCreatedBricks = 0;
    int numActiveBalls = 0;
    int destroyedBrickCount = 0;

    uint16_t score = 0;
    std::string scoreText = "0";

    uint8_t bricksNeededForNextBall = 2;
    uint8_t bricksSinceLastBall = 0;

    Sound destroyWav;
    void fillWithLeadingZeroes(std::string& str, int maxDigits)
    {
        int amount = maxDigits - str.length() - 1;
        for (int i = 0; i < amount; i++)
            str = "0" + str;
    }
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


    void drawUIText();

    void drawRenderTexture();

    void onBrickDestroyed(int index);

    void onBallLeftScreen(int index);

    void onBallShot();

    bool setup();

    void reset();

    void listLevels();

    public:
        Game(RenderTexture2D& target, Data& data);
        void run();
};