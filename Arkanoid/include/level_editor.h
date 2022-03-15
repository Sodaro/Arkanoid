#pragma once
#include "config.h"
#include "editor_brick.h"
#include <raylib.h>
#include <string>
#include <vector>
#include "entity_data.h"
class LevelEditor
{
    //float time_between_clicks = 0.5f;
    //float click_timer = 0;
    Data* data;
    std::vector<std::string> levels;
    std::string currentPath;
    EditorBrick bricks[num_max_bricks+1];
    RenderComponent renderers[num_max_bricks+1];
    RenderTexture2D targetTexture;
    void writeLevelToFile();
    void openLevel(std::string& path);
    void listLevels();
    
public:
    LevelEditor(RenderTexture2D& targetTexture, Data& data);
    void run();
};