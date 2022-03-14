#pragma once
#include "config.h"
#include "editor_brick.h"
#include <raylib.h>
#include <string>
class LevelEditor
{
    //float time_between_clicks = 0.5f;
    //float click_timer = 0;
    EditorBrick bricks[num_max_bricks+1];
    RenderComponent renderers[num_max_bricks+1];
    RenderTexture2D targetTexture;
    void writeLevelToFile();
    void openLevel(std::string& path);
    void previewLevel();
    
public:
    LevelEditor(RenderTexture2D& targetTexture);
    void run();
};