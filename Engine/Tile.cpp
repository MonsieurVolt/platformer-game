#include "Tile.h"
#include "SpriteEffect.h"

Tile::Tile(const Surface& surf, RectI f, RectI d, bool solid) : s(surf), frame(f), dim(d), isSolid(solid) {
    OutputDebugString(L"Construct tile");
};

void Tile::DrawTile(VecI2& pos, Graphics& gfx) {
    if (isSolid) {
        gfx.DrawSprite(pos.x, pos.y, frame, s, Chroma{ Colors::Magenta });
    }
}



