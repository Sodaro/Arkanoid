#include "level_editor.h"
#include <fstream>
#include <string>
#include <iostream>
#include "input.h"
#include "ui_helper.h"
#include "utilities.h"
#include "render_component.h"
LevelEditor::LevelEditor(RenderTexture2D& targetTexture, Data& data)
{
    state = State::Edit;
    this->targetTexture = targetTexture;
    this->data = &data;
}

void LevelEditor::writeLevelToFile()
{
    std::ofstream file(Utilities::levels_path + fileName + ".txt");
    std::string line;
    if (file.is_open())
    {
        for (int i = 0; i < num_max_bricks; i++)
        {
            line += bricks[i].key;
            if (i % bricksPerRow == bricksPerRow-1)
            {
                file << line << "\n";
                line = "";
            }
        }
    }
}

void LevelEditor::openLevel(std::string& name)
{
    std::ifstream file(Utilities::levels_path + name);
    std::string line;
    int index = 0;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                index++;
                if (index > num_max_bricks)
                    break;
                Data::BrickData brData = data->brickData[line[i]];
                bricks[index].changeTypeAndColor(line[i], brData.color1, brData.color2, brData.outline);
            }
        }
    }
}

void LevelEditor::openUpdate()
{
    /*
    * 1. create scroll wheel of levels
    * 2. let user choose by navigating with arrows and hitting enter/space
    * 3. open selected level
    */

    int prevIndex = -1, nextIndex = -1;

    int levelCount = (int)levels.size();
    if (levelCount == 0)
    {
        state = State::Edit;
        return;
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
    Vector2 topPos = { game_width / 2, game_height / 2 - 50 };
    Vector2 midPos = { game_width / 2, game_height / 2 };
    Vector2 botPos = { game_width / 2, game_height / 2 + 50 };

    if (prevIndex != -1)
    {
        UI::drawCenteredTextWithBox(levels[prevIndex], fontSize, topPos, GRAY, GRAY);
    }

    UI::drawCenteredTextWithBox(levels[openSelectedIndex], fontSize, midPos, WHITE, WHITE);
    if (nextIndex != -1)
    {
        UI::drawCenteredTextWithBox(levels[nextIndex], fontSize, botPos, GRAY, GRAY);
    }
    DrawText("Enter/Space: play", 0, game_height - 20, 12, WHITE);
    DrawText("UP/DOWN: navigate", 0, game_height - 40, 12, WHITE);

    if (Input::actionPressed())
    {
        openLevel(levels[openSelectedIndex]);
        state = State::Edit;
    }
}

void LevelEditor::writeUpdate()
{
    /*
    * 1. show & update field where user can write level name
    * 2. write level to file
    */
    UI::drawTextCentered(fileName, 8, Vector2{ game_width / 2, game_height / 2 }, WHITE);
    int key = GetCharPressed();
    int letterCount = (int)fileName.length();
    int maxLength = 10;
    if (std::isalnum(key) && letterCount < maxLength)
    {
        fileName += (char)key;
    }
    if (IsKeyDown(KEY_BACKSPACE) && letterCount > 0)
    {
        fileName.erase(fileName.end() - 1);
    }
    if (Input::actionPressed())
    {
        writeLevelToFile();
        state = State::Edit;
    }
}

void LevelEditor::editUpdate()
{
    float mouseWheel = GetMouseWheelMove();
    Data::BrickData brData;
    if (mouseWheel != 0)
    {
        int dir = mouseWheel > 0 ? 1 : -1;
        blockBrushIndex += dir;
        int keyCount = (int)data->keys.size();
        if (blockBrushIndex < 0)
            blockBrushIndex = keyCount-1;
        else if (blockBrushIndex >= keyCount)
            blockBrushIndex = 0;

        char key = data->keys[blockBrushIndex];
        brData = data->brickData[key];
        bricks[num_max_bricks].changeTypeAndColor(key, brData.color1, brData.color2, brData.outline);
        
    }

    if (IsKeyPressed(KEY_O))
    {
        std::size_t pos{};
        std::string input;
        int index = 0;
        levels = Utilities::fetchLevels();
        state = State::Open;
    }

    if (IsKeyPressed(KEY_S))
    {
        state = State::Write;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition() / 2;
        for (int i = 0; i < num_max_bricks; i++)
        {
            Vector2 pos = bricks[i].pos;
            Vector2 size = bricks[i].size;
            Rectangle rec = { pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y };
            if (CheckCollisionPointRec(mousePos, rec))
            {
                char key = data->keys[blockBrushIndex];
                brData = data->brickData[key];
                bricks[i].changeTypeAndColor(key, brData.color1, brData.color2, brData.outline);
                break;
            }
        }
    }

    for (int i = 0; i < num_max_bricks + 1; i++)
    {
        renderers[i].update(RenderComponent::Mode::FILL_LINES);
    }
    DrawText("Current type: ", 0, game_height - 100, 8, WHITE);
    DrawText("MWHEEL: change type.", 0, game_height - 80, 8, WHITE);
    DrawText("LMB: change brick to type.", 0, game_height - 60, 8, WHITE);
    DrawText("O: open level.", 0, game_height - 40, 8, WHITE);
    DrawText("S: save level.", 0, game_height - 20, 8, WHITE);

}

OP_CODE LevelEditor::run()
{
    int brickOffsetX = (int)bricks[0].size.x / 2;
    int brickOffsetY = (int)bricks[0].size.y / 2;

    int width = 40;
    int height = 20;
    for (int i = 0; i < num_max_bricks; i++)
    {
        int x = i % bricksPerRow;
        int y = i / bricksPerRow;
        EditorBrick& brick = bricks[i];
        RenderComponent* renderer = &renderers[i];
        brick.renderer = renderer;
        brick.pos = Vector2{ x * brick.size.x + brickOffsetX, y * brick.size.y + brickOffsetY };
        brick.changeTypeAndColor('1', data->brickData['1'].color1, data->brickData['1'].color2, data->brickData['1'].outline);
        renderer->pos = &brick.pos;
        renderer->size = brick.size;
        renderer->color1 = &brick.color1;
        renderer->color2 = &brick.color2;
        renderer->outline = &brick.outline;
        renderer->isVisible = true;
    }
    //create preview brick
    EditorBrick& brick = bricks[num_max_bricks];
    RenderComponent* renderer = &renderers[num_max_bricks];
    brick.renderer = renderer;
    brick.pos = Vector2{ game_width/2 - 20, game_height-85-brick_height/2 };
    brick.changeTypeAndColor('1', data->brickData['1'].color1, data->brickData['1'].color2, data->brickData['1'].outline);
    renderer->pos = &brick.pos;
    renderer->size = brick.size;
    renderer->color1 = &brick.color1;
    renderer->color2 = &brick.color2;
    renderer->outline = &brick.outline;
    renderer->isVisible = true;

    state = State::Edit;
    bool isRunning = true;
    OP_CODE returnCode = OP_CODE::SUCCESS;

    while (isRunning)
    {
        BeginTextureMode(targetTexture);

        ClearBackground(BLACK);

        switch (state)
        {
        case LevelEditor::State::Edit:
            editUpdate();
            Vector2 mousePos = GetMousePosition() / 2;
            UI::drawCursor(mousePos, MAGENTA);
            break;
        case LevelEditor::State::Open:
            openUpdate();
            break;
        case LevelEditor::State::Write:
            writeUpdate();
            break;
        default:
            break;
        }

        EndTextureMode();

        BeginDrawing();
        DrawTexturePro(targetTexture.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);

        EndDrawing();
        if (IsKeyPressed(KEY_ESCAPE))
        {
            isRunning = false;
            returnCode = OP_CODE::EXIT;
        }
        else if (WindowShouldClose())
        {
            isRunning = false;
            returnCode = OP_CODE::APPLICATION_QUIT;
        }
    }
    return returnCode;
}
