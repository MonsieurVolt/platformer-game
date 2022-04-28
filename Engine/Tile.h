#pragma once
#include "Surface.h"
#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
class Tile
{
public:

    Tile(const Surface& s, RectI frame, RectI dim, bool solid);


 
    virtual ~Tile() {
        OutputDebugString(L"dete");
    }
    virtual void DrawTile(VecI2& pos, Graphics& gfx);
protected:
    RectI dim;
    RectI frame;
    const Surface& s;
    bool isSolid;

};

