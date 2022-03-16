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
            //std::cout << bricks[i].pos.x << ", " << bricks[i].pos.y << std::endl;
            switch (bricks[i].type)
            {
                case Data::BrickType::None:   line += '0'; break;
                case Data::BrickType::One:  line += '1'; break;
                case Data::BrickType::Two: line += '2'; break;
                case Data::BrickType::Three:   line += '3'; break;
                case Data::BrickType::Four: line += '4'; break;
                case Data::BrickType::Five:    line += '5'; break;
                case Data::BrickType::Six:   line += '6'; break;
                default:
                    break;
            }
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
                int brickTypeIndex = line[i] - '0';
                if (brickTypeIndex < (int)Data::BrickType::Count)
                {
                    Data::BrickData brData = data->brickData[brickTypeIndex];
                    bricks[index].changeTypeAndColor((Data::BrickType)brickTypeIndex, brData.color1, brData.color2, brData.outline);
                }
                index++;
                if (index > num_max_bricks)
                    break;
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
    Vector2 playBtnPos = { game_width / 2, game_height / 2 - 50 };
    Vector2 editorBtnPos = { game_width / 2, game_height / 2 };
    Vector2 quitBtnPos = { game_width / 2, game_height / 2 + 50 };

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
        if (blockBrushIndex < 0)
            blockBrushIndex = (int)Data::BrickType::Count - 1;
        else if (blockBrushIndex >= (int)Data::BrickType::Count)
            blockBrushIndex = 0;

        brData = data->brickData[blockBrushIndex];
        bricks[num_max_bricks].changeTypeAndColor((Data::BrickType)blockBrushIndex, brData.color1, brData.color2, brData.outline);
        
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
                brData = data->brickData[blockBrushIndex];
                bricks[i].changeTypeAndColor((Data::BrickType)blockBrushIndex, brData.color1, brData.color2, brData.outline);
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

void LevelEditor::run()
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
        brick.changeTypeAndColor((Data::BrickType)1, data->brickData[1].color1, data->brickData[1].color2, data->brickData[1].outline);
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
    brick.changeTypeAndColor((Data::BrickType)1, data->brickData[1].color1, data->brickData[1].color2, data->brickData[1].outline);
    renderer->pos = &brick.pos;
    renderer->size = brick.size;
    renderer->color1 = &brick.color1;
    renderer->color2 = &brick.color2;
    renderer->outline = &brick.outline;
    renderer->isVisible = true;

    state = State::Edit;

    while (!WindowShouldClose())
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
    }
}
