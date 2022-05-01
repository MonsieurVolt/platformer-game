#pragma once
#include "Vec2.h"
template<typename T>
class Rect
{
public:
    Rect(T _t, T _b, T _l, T _r) : top(_t), bottom(_b), right(_r), left(_l) {};
    Rect(Vec2<T>& topLeft, T width, T height) : top(topLeft.y), left(topLeft.x), bottom(topLeft.y + height), right(topLeft.x + width) {};
    Rect(Vec2<T>& topLeft, Vec2<T>& bottomRight) : top(topLeft.y), bottom(bottom.y), left(topLeft.x), right(bottomRight.x) {};

    bool IsOverlappingWith(const Rect& other) const {
        return right > other.left && left<other.right&& bottom>other.top && top < other.bottom;
    }
    bool IsContainedBy(const Rect& other) const {
        return top >= other.top && bottom <= other.bottom && left >= other.left && right <= other.right;
    }
    bool Contains(const Rect& other) const {
        return top <= other.top && bottom >= other.bottom && left <= other.left && right >= other.right;
    }
    Rect FromCenter(const Vec2<T>& center, T halfWidth, T halfHeight) {
        const Vec2<T> half(halfWidth, halfHeight);
        return Rect(center - half, center + half);
    }
    T GetWidth() const {
        return right - left;
    }
    T GetHeight() {
        return bottom - top;
    }
    Rect GetExpanded(T offset) const
    {
        return Rect(left - offset, right + offset, top - offset, bottom + offset);
    }
    Vec2<T> GetCenter() const
    {
        return Vec2<T>((left + right) / (T)2, (top + bottom) / (T)2);
    }
    Rect<T>& operator+(const VecF2& vec) {
        return Rect<T>(top + vec.y, bottom + vec.y, left + vec.x, right + vec.x);
    }
public:
    T top;
    T bottom;
    T left;
    T right;
};

typedef Rect<int> RectI;
typedef Rect<float> RectF;