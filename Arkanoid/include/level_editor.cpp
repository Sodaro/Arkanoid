#include "level_editor.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

LevelEditor::LevelEditor(RenderTexture2D& targetTexture, Data& data)
{
    this->targetTexture = targetTexture;
    this->data = &data;
}

void LevelEditor::writeLevelToFile()
{
    if (currentPath == "")
        currentPath = "defaultlevel.txt";

    std::ofstream file(currentPath);
    std::string line;
    if (file.is_open())
    {
        for (int i = 0; i < num_max_bricks; i++)
        {
            //std::cout << bricks[i].pos.x << ", " << bricks[i].pos.y << std::endl;
            switch (bricks[i].type)
            {
                case Data::BrickType::One:  line += 'g'; break;
                case Data::BrickType::Two: line += 'p'; break;
                case Data::BrickType::Three:   line += 'b'; break;
                case Data::BrickType::Four: line += 'y'; break;
                case Data::BrickType::Five:    line += 'r'; break;
                case Data::BrickType::Six:   line += 'G'; break;
                case Data::BrickType::None:   line += 'n'; break;
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
                    case 'G': bricks[index].changeTypeAndColor(Data::BrickType::Six, data->brickData[5].color1);   break;
                    case 'y': bricks[index].changeTypeAndColor(Data::BrickType::Four, data->brickData[3].color1); break;
                    case 'r': bricks[index].changeTypeAndColor(Data::BrickType::Five, data->brickData[4].color1);    break;
                    case 'p': bricks[index].changeTypeAndColor(Data::BrickType::Two, data->brickData[1].color1); break;
                    case 'b': bricks[index].changeTypeAndColor(Data::BrickType::Three, data->brickData[2].color1);   break;
                    case 'g': bricks[index].changeTypeAndColor(Data::BrickType::One, data->brickData[0].color1);  break;
                    case 'n': bricks[index].changeTypeAndColor(Data::BrickType::None, data->brickData[6].color1);   break;
                }
                index++;
                if (index > num_max_bricks)
                    break;
            }
        }
    }
}
void LevelEditor::listLevels()
{
    levels.clear();
    std::string path = std::filesystem::current_path().string();
    for (const auto& file : std::filesystem::directory_iterator(path))
    {
        std::filesystem::path name = file.path().filename();
        if (name.extension() == ".txt")
        {
            std::cout << "[" << levels.size() << "] - " << name << std::endl;
            levels.push_back(name.string());
        }
    }
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
        brick.type = (Data::BrickType)0;
        brick.color = WHITE;
        renderer->pos = &brick.pos;
        renderer->size = brick.size;
        renderer->color1 = &brick.color;
        renderer->isVisible = true;
    }
    //create preview brick
    EditorBrick& brick = bricks[num_max_bricks];
    RenderComponent* renderer = &renderers[num_max_bricks];
    brick.renderer = renderer;
    brick.pos = Vector2{ game_width/2 - 20, game_height-85-brick_height/2 };
    brick.type = (Data::BrickType)0;
    brick.color = GREEN;
    renderer->pos = &brick.pos;
    renderer->size = brick.size;
    renderer->color1 = &brick.color;
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
            type_index %= (int)Data::BrickType::Count;
            bricks[num_max_bricks].changeTypeAndColor((Data::BrickType)type_index, data->brickData[type_index].color1);
        }
        else if (mouseWheel < 0)
        {
            type_index--;
            if (type_index < 0)
            {
                type_index = (int)Data::BrickType::None;
            }
            bricks[num_max_bricks].changeTypeAndColor((Data::BrickType)type_index, data->brickData[type_index].color1);
        }
        
        
        if (IsKeyPressed(KEY_O))
        {
            std::size_t pos{};
            std::string input;
            int index = 0;
            system("cls");
            listLevels();
            if (levels.size() == 0)
                std::cout << "No levels found" << std::endl;
            else
            {
                std::cout << "Select file to open (index number): " << std::endl;
                try
                {
                    bool validIndex = true;
                    do
                    {
                        if (!validIndex)
                            std::cout << "No level with given index" << std::endl;

                        validIndex = false;
                        std::cin >> input;
                        index = std::stoi(input);
                    } while (index < 0 || index > levels.size());
                    currentPath = levels[index];
                    openLevel(currentPath);
                }
                catch (std::invalid_argument const& ex)
                {
                    std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
                }
                catch (std::out_of_range const& ex)
                {
                    std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
                    const long long ll{ std::stoll(input, &pos) };
                    std::cout << "std::stoll('" << input << "'): " << ll << "; pos: " << pos << '\n';
                }
            }
        }
        if (IsKeyPressed(KEY_S))
        {
            writeLevelToFile();
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
                    bricks[i].changeTypeAndColor((Data::BrickType)type_index, data->brickData[type_index].color1);
                    break;
                }
            }
        }

        for (int i = 0; i < num_max_bricks+1; i++)
        {
            renderers[i].update(RenderComponent::Mode::FILL_LINES);
        }

        DrawText("Current type: ", 0, game_height - 100, 8, WHITE);
        DrawText("MWHEEL: change type." , 0, game_height - 80, 8, WHITE);
        DrawText("LMB: change brick to type.", 0, game_height - 60, 8, WHITE);
        DrawText("O: open level (console).", 0, game_height - 40, 8, WHITE);
        DrawText("S: save level.", 0, game_height - 20, 8, WHITE);


        EndTextureMode();

        BeginDrawing();
        DrawTexturePro(targetTexture.texture, Rectangle{ 0,0,game_width, -game_height }, Rectangle{ 0,0, screen_width, screen_height }, Vector2{ 0,0 }, 0, WHITE);
        EndDrawing();
    }
}
