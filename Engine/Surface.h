#pragma once
#include <string>
#include <vector>
#include "Colors.h"
#include "Rect.h"

class Surface
{
public:
    Surface() = default;
    Surface(const Surface&) = delete;
     Surface(Surface&& donor);
    Surface& operator=(const Surface& s) = delete;
    Surface& operator=(Surface&& rhs);
    Surface(int width, int height);
    Surface(int width, int height, Color c);
    Surface(const std::string& filename);
    ~Surface() = default;
    void PutPixel(int x, int y, Color c);
    Color GetPixel(int x, int y) const;
    int GetWidth() const;
    int GetHeight() const;
    RectI GetRect() const;

    const Color* Data() const;
private:
    int width = 0;
    int height = 0;
    std::vector<Color> pixels;



};

