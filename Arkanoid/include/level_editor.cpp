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
void LevelEditor::listLevels()
{
    levels.clear();
    std::string path = std::filesystem::current_path().string() + ".\\levels\\";
    for (const auto& file : std::filesystem::directory_iterator(path))
    {
        std::filesystem::path name = file.path().filename();
        std::string name_no_extension = "";
        if (name.extension() == ".txt")
        {
            name_no_extension = name.string().substr(0, name.string().find_last_of('.'));
            std::cout << "[" << levels.size() << "] - " << name_no_extension << std::endl;
            levels.push_back(".\\levels\\" + name.string());
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
            bricks[num_max_bricks].changeTypeAndColor((Data::BrickType)type_index, data->brickData[type_index].color1, data->brickData[type_index].color2, data->brickData[type_index].outline);
        }
        else if (mouseWheel < 0)
        {
            type_index--;
            if (type_index < 0)
            {
                type_index = (int)Data::BrickType::Count - 1;
            }
            bricks[num_max_bricks].changeTypeAndColor((Data::BrickType)type_index, data->brickData[type_index].color1, data->brickData[type_index].color2, data->brickData[type_index].outline);
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
                    } while (index < 0 || index >= levels.size());
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
        
        bool ctrlMod = IsKeyDown(KEY_LEFT_CONTROL);
        if (IsKeyPressed(KEY_S))
        {
            if (ctrlMod)
            {
                
                system("cls");
                std::cout << "Existing levels:" << std::endl;
                listLevels();
                std::cout << "Save level as: ";
                std::cin >> currentPath;
                currentPath = ".\\levels\\" + currentPath + ".txt";
            }
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
                    bricks[i].changeTypeAndColor((Data::BrickType)type_index, data->brickData[type_index].color1, data->brickData[type_index].color2, data->brickData[type_index].outline);
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
