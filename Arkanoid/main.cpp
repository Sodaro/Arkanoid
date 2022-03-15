#include "raylib.h"
#include "config.h"
#include "game.h"
#include "level_editor.h"
#include <fstream>
#include <json.hpp>
#include "game_data.h"

Data data;
void drawMenu(int selectedIndex)
{
    int fontSize = 16;
    const char* title = "Arkanoid!";
    const char* description = "Made by David Bang";
    DrawText(title, game_width/2 - 2 * fontSize, 0, 16, WHITE);
    DrawText(description, game_width/2 - 4 * 12, 20, 8, WHITE);
    Vector2 playBtnPos = { game_width / 2 - fontSize, game_height / 2 };
    Vector2 editorBtnPos = { game_width / 2 - fontSize, game_height / 2 + 50 };
    Vector2 quitBtnPos = { game_width / 2 - fontSize, game_height / 2 + 100 };
    if (selectedIndex == 0)
        DrawRectangleLines(playBtnPos.x - 20, playBtnPos.y - 5, 75, 25, WHITE);
    else if (selectedIndex == 1)
        DrawRectangleLines(editorBtnPos.x - 20, editorBtnPos.y - 5, 75, 25, WHITE);
    else
        DrawRectangleLines(quitBtnPos.x - 20, quitBtnPos.y - 5, 75, 25, WHITE);

    DrawText("Play", playBtnPos.x, playBtnPos.y, 16, WHITE);
    DrawText("Editor", editorBtnPos.x, editorBtnPos.y, 16, WHITE);
    DrawText("Quit", quitBtnPos.x, quitBtnPos.y, 16, WHITE);
}

Color getColorFromJSON(nlohmann::json& colorArr)
{
    return Color { colorArr[0].get<unsigned char>(), colorArr[1].get<unsigned char>(), colorArr[2].get<unsigned char>(), colorArr[3].get<unsigned char>() };
}

void parseJSONData()
{
    std::ifstream file("game_data.json");
    nlohmann::json j;
    file >> j;
    int index = 0;
    for (auto& obj : j["bricks"])
    {
        data.brickData[index].color1 = getColorFromJSON(obj["color1"]);
        data.brickData[index].color2 = getColorFromJSON(obj["color2"]);
        data.brickData[index].outline = getColorFromJSON(obj["outline"]);
        data.brickData[index].score = obj["score"].get<int>();
        data.brickData[index].health = obj["health"].get<int>();
        index++;
    }
    data.ballData.color1 = getColorFromJSON(j["ball"]["color1"]);
    data.ballData.color2 = getColorFromJSON(j["ball"]["color2"]);
    data.ballData.outline = getColorFromJSON(j["ball"]["outline"]);

    data.playerData.color1 = getColorFromJSON(j["player"]["color1"]);
    data.playerData.color2 = getColorFromJSON(j["player"]["color2"]);
    data.playerData.outline = getColorFromJSON(j["player"]["outline"]);
}

void drawMenu(RenderTexture2D target, int selectedIndex)
{
    BeginTextureMode(target);
    ClearBackground(BLACK);

    drawMenu(selectedIndex);

    EndTextureMode();

    BeginDrawing();
    DrawTexturePro(target.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
    EndDrawing();
}


int main()
{
    enum class State { Menu, InGame, Editor };
    InitWindow(screen_width, screen_height, "Arkanoid - David Bang");
    InitAudioDevice();
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(game_width, game_height);
    State state = State::Menu;

    parseJSONData();

    Game game{ target, data };
    LevelEditor editor{target, data};

    int choice = 1, selectedIndex = 0;
    bool running = true;

    while (running)
    {
        switch (state)
        {
        case State::Menu:
        {
            int vertical = Input::getVerticalInput();
            if (vertical < 0)
            {
                selectedIndex--;
                if (selectedIndex < 0)
                    selectedIndex = 2;
            }
            else if (vertical > 0)
            {
                ++selectedIndex %= 3;
            }

            if (Input::actionPressed())
            {
                if (selectedIndex == 0)
                {
                    state = State::InGame;
                }
                else if (selectedIndex == 1)
                {
                    state = State::Editor;
                }
                else
                {
                    running = false;
                }
            }
            drawMenu(target, selectedIndex);
            break;
        }
        case State::InGame:
            game.run();
            state = State::Menu;
            break;
        case State::Editor:
            editor.run();
            state = State::Menu;
            break;
        default:
            break;
        }
    }

    UnloadRenderTexture(target);
    CloseWindow();


    return 0;
}