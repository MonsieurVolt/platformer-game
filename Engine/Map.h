#pragma once
#include <cassert>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "Graphics.h"
class Grid {
public:
    Grid() = default;
    Grid(std::string surfName);
    ~Grid();
    Grid& operator=(const Grid&) = default;
    Grid& operator=(const Grid&& other) noexcept;
    Grid(const Grid&) = default;
    Grid(const Grid&& other) noexcept;
    void DrawTiles(Graphics& gfx, int X);

protected:
    Surface* surface;
    int width;
    int height;
     int tileWidth = 64;
    std::vector<Tile*> tiles;
    std::vector<Tile*> map;

};
class Map :public Grid

{
public:
    enum class TypeTiles {
        Ground,
        Grass,
        Surprise,
        Air,
        End
    };
    Map(std::string surfName, std::string modelName, RectI& frames);





};

