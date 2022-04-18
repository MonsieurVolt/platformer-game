#pragma once
#include <cassert>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "Graphics.h"
class Map

{
public:
    enum class TypeTiles {
        Ground,
        Grass,
        Surprise,
        Air,
        End
    };
    Map() = default;
    Map(const Surface& s, std::string filename, RectI& frames);
    void DrawTiles(Graphics& gfx, int X);
private:


    const Surface& surface;
    int width = 0;
    int height = 0;
    int tileWidth = 64;

    std::vector<Tile*> tiles;
    std::vector<Tile*> map;
};

