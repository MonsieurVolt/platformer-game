#include "Map.h"
#include "SpriteEffect.h"

Map::Map(std::string surfName, std::string modelName, RectI& frames) : Grid(surfName)
{
    std::fstream file(modelName);
    assert(file);
    RectI frame = frames;
    for (int i = 0; i < (int)TypeTiles::Air; i++) {

        tiles.push_back(new Tile(new RectI(frame), true));
        frame.left = frame.right;
        frame.right += frames.right;
    }
    tiles.push_back(new Tile());
    for (std::string line; std::getline(file, line);) {
  
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
        for (int j = 0; j < 18; j++) {
            if (!map[i * width + nbTilePass + j]->IsEmpty()){
            gfx.DrawTile(j * 64 + posFirst, i * 64, map[i * width + nbTilePass + j]->getFrame(), *surface);
            }
        }
    }
}
void Map::DrawTiles(Graphics& gfx, int X)
{
    int nbTilePass = (X - (X % tileWidth)) / tileWidth;


    int posFirst = nbTilePass * tileWidth - X;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 18; j++) {
            if (!map[i * width + nbTilePass + j]->IsEmpty()) {
                if (nbTilePass > 20) {
                   
                }
                gfx.DrawTile(j * 64 + posFirst, i * 64, map[i * width + nbTilePass + j]->getFrame(), *surface);
            }
        }
    }
}
void Map::HandleCharacter(RectF& persoPos, VecF2& dir, int X,Character& mario) {
    int nbTilePass = (X - (X % tileWidth)) / tileWidth;

    int posFirst = nbTilePass * tileWidth - X;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 18; j++) {
            if (!map[i * width + nbTilePass + j]->IsEmpty()) {
                RectF tileRect = RectF(VecF2( j * 64 + posFirst, i * 64 ), tileWidth, tileWidth);
                if (tileRect.IsOverlappingWith(persoPos+dir)) {
                    if ((persoPos + dir).bottom > tileRect.top && persoPos.right  > tileRect.left+6 && persoPos.left < tileRect.right-6 && persoPos.top < tileRect.top) {
                        dir.y = -(persoPos.bottom - tileRect.top);
                    }
                    if (persoPos.bottom > tileRect.bottom && persoPos.right > tileRect.left+6 && persoPos.left < tileRect.right-6 && (persoPos+dir).top < tileRect.bottom) {
                        dir.y = (tileRect.bottom - persoPos.top);
                        mario.SetJump(false);
                    }
                    if (persoPos.bottom > tileRect.top && persoPos.top+2 < tileRect.bottom && (persoPos+dir).right > tileRect.left && persoPos.left < tileRect.right) {
                        dir.x = -(persoPos.right - tileRect.left);
                    }
                    if (persoPos.bottom > tileRect.top && persoPos.top+2 < tileRect.bottom && persoPos.right > tileRect.right && (persoPos+dir).left < tileRect.right) {
                        dir.x = (tileRect.right - persoPos.left);
                    }
               }
            }
        }
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

 Background::Background(std::string surfName, std::string modelName, RectI& frames): Grid(surfName)
 {
     std::fstream file(modelName);
     assert(file);
 
     tiles.push_back(new Tile(new RectI(frames), true));
     tiles.push_back(new Tile());

     for (std::string line; std::getline(file, line);) {

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
                     map.push_back(tiles[(int)TypeTiles::Cloud]);
                     break;
             
                     break;
                 default:

                     map.push_back(tiles[(int)TypeTiles::Sky]);
                     break;
                 }
             }

         }
     }
 }
