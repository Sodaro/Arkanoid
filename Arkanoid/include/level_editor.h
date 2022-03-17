#pragma once
#include <string>
#include <vector>
#include "config.h"
#include "editor_brick.h"
#include "render_component.h"

class LevelEditor
{
    enum class State { Edit, Open, Write };
    State state;
    Data* data;
    std::vector<std::string> levels;
    EditorBrick bricks[num_max_bricks+1];
    RenderComponent renderers[num_max_bricks+1];
    RenderTexture2D targetTexture;

    int openSelectedIndex = 0;
    int blockBrushIndex = 0;
    std::string fileName = "mylvlname";

    void writeLevelToFile();
    void openLevel(std::string& path);
    void editUpdate();
    void openUpdate();
    void writeUpdate();
public:
    LevelEditor(RenderTexture2D& targetTexture, Data& data);
    OP_CODE run();
};