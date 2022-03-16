#include "utilities.h"
#include <filesystem>
#include "raylib.h"

typedef unsigned char u_char;

std::vector<std::string> Utilities::fetchLevels()
{
    std::vector<std::string> levels;
    std::string path = std::filesystem::current_path().string() + ".\\levels\\";
    for (const auto& file : std::filesystem::directory_iterator(path))
    {
        std::filesystem::path name = file.path().filename();
        std::string name_no_extension = "";
        if (name.extension() == ".txt")
        {
            name_no_extension = name.string().substr(0, name.string().find_last_of('.'));
            levels.push_back(name.string());
        }
    }
    return levels;
}

float Utilities::easeInQuart(float x)
{
    return x * x * x * x;
}

float Utilities::easeOutQuart(float x)
{
    return 1 - powf(1 - x, 4);
}

Color Utilities::lerpColor(Color& c1, Color& c2, float t)
{
    Color newColor = {
        (u_char)(c1.r + t * (c2.r - c1.r)),
        (u_char)(c1.g + t * (c2.g - c1.g)),
        (u_char)(c1.b + t * (c2.b - c1.b)),
        (u_char)(c1.a + t * (c2.a - c1.a))
    };
    return newColor;
}

Color Utilities::easeInColor(Color& c1, Color& c2, float t)
{
    t = easeInQuart(t);
    return Color{
        (u_char)(c1.r + t * (c2.r - c1.r)),
        (u_char)(c1.g + t * (c2.g - c1.g)),
        (u_char)(c1.b + t * (c2.b - c1.b)),
        (u_char)(c1.a + t * (c2.a - c1.a)) };
}

Color Utilities::easeOutColor(Color& c1, Color& c2, float t)
{
    t = easeOutQuart(t);
    return Color{
        (u_char)(c1.r + t * (c2.r - c1.r)),
        (u_char)(c1.g + t * (c2.g - c1.g)),
        (u_char)(c1.b + t * (c2.b - c1.b)),
        (u_char)(c1.a + t * (c2.a - c1.a))};
}

void Utilities::fillWithLeadingZeroes(std::string& str, int maxDigits)
{
    int amount = maxDigits - (int)str.length() - 1;
    for (int i = 0; i < amount; i++)
        str = "0" + str;
}
