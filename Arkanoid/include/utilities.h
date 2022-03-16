#pragma once
#include <vector>
#include <string>
struct Color;
namespace Utilities
{
    const std::string levels_path = ".\\levels\\";
    const std::string resource_path = ".\\resources\\";
    std::vector<std::string> fetchLevels();


    float easeInQuart(float x);
    float easeOutQuart(float x);

    Color lerpColor(Color& c1, Color& c2, float t);
    Color easeInColor(Color& c1, Color& c2, float t);
    Color easeOutColor(Color& c1, Color& c2, float t);
    void fillWithLeadingZeroes(std::string& str, int maxDigits);
}