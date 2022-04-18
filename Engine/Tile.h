#pragma once
#include "Surface.h"
#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
class Tile
{
public:
    Tile() = default;
    Tile(const Surface& s, RectI frame, RectI dim, bool solid);
    Tile(const Tile&) = default;

    Tile& operator=(const Tile& other) = default;
    Tile& operator=(const Tile&& other);
    virtual ~Tile() = default;
    virtual void DrawTile(VecI2& pos, Graphics& gfx);
protected:
    RectI dim;
    RectI frame;
    const Surface& s;
    bool isSolid;

};

