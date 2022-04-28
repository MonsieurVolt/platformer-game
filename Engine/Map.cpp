#include "Map.h"


Map::Map(std::string surfName, std::string modelName, RectI& frames) : Grid(surfName)
{
    std::fstream file(modelName);
    assert(file);
    RectI frame = frames;
    for (int i = 0; i < (int)TypeTiles::Air; i++) {

        tiles.push_back(new Tile(*surface, frame, frames, true));
        frame.left = frame.right;
        frame.right += frames.right;
    }
    tiles.push_back(new Tile(Surface{ 64,64 }, frames, frames, false));
    for (std::string line; std::getline(file, line);) {
        OutputDebugStringA(line.c_str());
        if (line == "[width]") {
            file >> width;

        }
        else if (line == "[height]") {
            file >> height;

        }
        else if (line == "[TileWidth]") {
            file >> tileWidth;
        }
        else if (line[0] == '/') {

            line.resize(width + 1);

            for (int j = 1; j < width + 1; j++) {
                switch (line[j])
                {
                    case '#':
                    map.push_back(tiles[(int)TypeTiles::Grass]);
                    break;
                    case '?':
                    map.push_back(
                        tiles[(int)TypeTiles::Surprise]);
                    break;
                    case '-':
                    map.push_back(tiles[(int)TypeTiles::Ground]);
                    break;
                    default:

                    map.push_back(tiles[(int)TypeTiles::Air]);
                    break;
                }
            }

        }
    }
}
 Grid::Grid(const Grid&& other) noexcept {
    *this = other;
}
void Grid::DrawTiles(Graphics& gfx, int X)
{
    int nbTilePass = (X - (X % tileWidth)) / tileWidth;


    int posFirst = nbTilePass * tileWidth - X;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 18; j++)

            map[i * width + nbTilePass + j]->DrawTile(VecI2{ j * 64 + posFirst,i * 64 }, gfx);
    }
}

Grid::Grid(std::string surfName):width(0),height(0)
    
{
    surface = new Surface(surfName);
}

 Grid::~Grid() {
    tiles.clear();
    map.clear();
}

 Grid& Grid::operator=(const Grid&& other) noexcept
 {
     width = other.width;
     height = other.height;
     tileWidth = other.tileWidth;
     tiles = std::move(other.tiles);
     map = std::move(other.map);
     return *this;
 }