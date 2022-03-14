#include "level_editor.h"
#include <fstream>
#include <string>
#include <iostream>
#include "raygui.h"


LevelEditor::LevelEditor(RenderTexture2D& targetTexture)
{
    this->targetTexture = targetTexture;
}

void LevelEditor::writeLevelToFile()
{
    std::ofstream file("level.txt");
    std::string line;
    if (file.is_open())
    {
    }
}

void LevelEditor::openLevel(std::string& path)
{
    std::ifstream file(path);
    std::string line;
    int index = 0;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                switch (line[i])
                {
                case 'G':
                    bricks[index].changeType(BrickType::Gray);
                    break;
                case 'y':
                    bricks[index].changeType(BrickType::Yellow);
                    break;
                case 'r':
                    bricks[index].changeType(BrickType::Red);
                    break;
                case 'p':
                    bricks[index].changeType(BrickType::Purple);
                    break;
                case 'b':
                    bricks[index].changeType(BrickType::Blue);
                    break;
                case 'g':
                    bricks[index].changeType(BrickType::Green);
                    break;
                case 'n':
                    bricks[index].changeType(BrickType::None);
                    break;
                }
                index++;
                if (index > num_max_bricks)
                    break;
            }
        }
    }
}

void LevelEditor::previewLevel()
{
}

void LevelEditor::run()
{
    //openFileDialog();
    int brickOffsetX = bricks[0].size.x / 2;
    int brickOffsetY = bricks[0].size.y / 2;

    for (int i = 0; i < num_max_bricks; i++)
    {
        int x = i % bricksPerRow;
        int y = i / bricksPerRow;
        EditorBrick& brick = bricks[i];
        RenderComponent* renderer = &renderers[i];
        brick.renderer = renderer;
        brick.pos = Vector2{ x * brick.size.x + brickOffsetX, y * brick.size.y + brickOffsetY };
        brick.type = (BrickType)0;
        brick.color = neon_green;
        renderer->pos = &brick.pos;
        renderer->size = brick.size;
        renderer->color = &brick.color;
        renderer->isVisible = true;
    }
    EditorBrick& brick = bricks[num_max_bricks];
    RenderComponent* renderer = &renderers[num_max_bricks];
    brick.renderer = renderer;
    brick.pos = Vector2{ game_width/2 + 20, game_height-80-brick_height/2 };
    brick.type = (BrickType)0;
    brick.color = neon_green;
    renderer->pos = &brick.pos;
    renderer->size = brick.size;
    renderer->color = &brick.color;
    renderer->isVisible = true;

    double time = 0;
    double prev_time = 0;
    double delta_time;

    int type_index = 0;

    while (!WindowShouldClose())
    {
        time = GetTime();
        delta_time = (time - prev_time);
        prev_time = time;
        //click_timer += delta_time;
        BeginTextureMode(targetTexture);

        ClearBackground(BLACK);
        float mouseWheel = GetMouseWheelMove();
        if (mouseWheel > 0)
        {
            type_index++;
            type_index %= (int)BrickType::Count;
            bricks[num_max_bricks].changeType((BrickType)type_index);
        }
        else if (mouseWheel < 0)
        {
            type_index--;
            if (type_index < 0)
            {
                type_index = (int)BrickType::None;
            }
            bricks[num_max_bricks].changeType((BrickType)type_index);
        }
        
        
        if (IsKeyPressed(KEY_O))
        {
            system("cls");
            std::cout << "Select file to open (format must be .txt): " << std::endl;
            std::string path;
            std::cin >> path;
            openLevel(path);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();
            for (int i = 0; i < num_max_bricks; i++)
            {
                Vector2 pos = bricks[i].pos;
                Vector2 size = bricks[i].size;
                Rectangle rec = { pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y/2 };
                if (CheckCollisionPointRec(mousePos, rec))
                {
                    bricks[i].changeType((BrickType)type_index);
                    break;
                }
            }
        }

        for (int i = 0; i < num_max_bricks+1; i++)
        {
            renderers[i].update(RenderComponent::Mode::FILL_LINES);
        }

        DrawText("Current type: ", 0, game_height - 100, 16, WHITE);
        DrawText("MWHEEL: change type." , 0, game_height - 50, 16, WHITE);
        DrawText("LMB: change brick to type.", 0, game_height - 20, 16, WHITE);


        EndTextureMode();

        BeginDrawing();
        DrawTexturePro(targetTexture.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
        EndDrawing();
    }
}
