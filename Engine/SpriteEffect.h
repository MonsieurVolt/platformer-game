#include "Colors.h"
#include "Graphics.h"
class Chroma {
public:
    Chroma(Color c) :
        chroma(c) {};
    void operator()(const Color& p, int x, int y, Graphics& g) {
        if (p != chroma) {
            g.PutPixel(x, y, p);
        }
        else {
            g.PutPixel(x, y, Colors::Blue);
        }
    }
private:
    Color chroma;
};