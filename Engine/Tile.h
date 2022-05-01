#pragma once
#include "Surface.h"
#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
class Tile
{
public:

    Tile( RectI *frame, bool solid);
    Tile() = default;


 
    virtual ~Tile() {
        OutputDebugString(L"dete");
    }

    RectI& getFrame()const {
        return *frame;
    }
    bool IsSolid() const {
        return isSolid;

    }
    bool IsEmpty() const {
        return isEmpty;
    }
protected:
    RectI* frame = nullptr;
    bool isSolid = false;
    bool isEmpty = true;

};

