#include "raylib.h"
#include "config.h"
#include "game.h"
#include "level_editor.h"
#include <fstream>
#include <json.hpp>
#include <string>
#include "game_data.h"
#include "ui_helper.h"

Data data;
void drawMenu(int selectedIndex)
{
    int fontSize = 16;
    std::string play = "Play";
    std::string editor = "Editor";
    std::string quit = "Quit";
    Color c1 = GRAY, c2 = GRAY, c3 = GRAY;
    DrawText("Arkanoid!", game_width/2 - 2 * fontSize, 0, fontSize, WHITE);
    DrawText("Made by David Bang", game_width/2 - 4 * 12, 20, 8, WHITE);
    if (selectedIndex == 0)
        c1 = WHITE;
    else if (selectedIndex == 1)
        c2 = WHITE;
    else
        c3 = WHITE;

    UI::drawCenteredTextWithBox(play, fontSize, Vector2{ game_width / 2, game_height / 2 }, c1, c1);
    UI::drawCenteredTextWithBox(editor, fontSize, Vector2{ game_width / 2, game_height / 2 + 50 }, c2, c2);
    UI::drawCenteredTextWithBox(quit, fontSize, Vector2{ game_width / 2, game_height / 2 + 100 }, c3, c3);
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
    //int index = 0;
    for (auto& obj : j["bricks"])
    {
        std::string key = obj["key"].get<std::string>();
        Data::BrickData brData;
        //data.brickData
        //brData.key = key;
        brData.color1 = getColorFromJSON(obj["color1"]);
        brData.color2 = getColorFromJSON(obj["color2"]);
        brData.outline = getColorFromJSON(obj["outline"]);
        brData.score = obj["score"].get<int>();
        brData.health = obj["health"].get<int>();

        data.brickData[key[0]] = brData;
        data.keys.push_back(key[0]);
        //index++;
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
    //Vector2 mousePos = GetMousePosition();
    //UI::drawCursor(mousePos, MAGENTA);
    EndTextureMode();
}


int main()
{
    enum class State { Menu, InGame, Editor };
    InitWindow(screen_width, screen_height, "Arkanoid - David Bang");
    InitAudioDevice();
    SetTargetFPS(60);
    HideCursor();

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

            if (Input::actionReleased())
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
            BeginDrawing();
            DrawTexturePro(target.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
            EndDrawing();
            break;
        }
        case State::InGame:
            if (game.levelSelectUpdate() == false)
            {
                if (game.state == Game::State::Gameplay)
                    game.run();

                state = State::Menu;
            }
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