#include "Surface.h"
#include <fstream>
#include "ChiliWin.h"
#include <cassert>

Surface::Surface(Surface&& s)
{
    OutputDebugString(L"Create instance");
    *this = std::move(s);
}

Surface& Surface::operator=(Surface&& s)
{
    OutputDebugString(L"Create instance");
    width = s.width;
    height = s.height;
    pixels = std::move(s.pixels);
    s.width = 0;
    s.height = 0;
    return *this;
}

Surface::Surface(int width, int height) :
    width(width),
    height(height)
{
    OutputDebugString(L"Create instance");
    pixels.resize(width * height);
}

Surface::Surface(int width, int height, Color c):width(width),height(height)
{
    OutputDebugString(L"Create instance");
    pixels.resize(width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            PutPixel(i, j, c);
        }
        
    }
}

Surface::Surface(const std::string& filename)
{
    OutputDebugString(L"Construct surface");
    std::ifstream file(filename, std::ios::binary);
    assert(file);
    BITMAPFILEHEADER bmpFileHeader;
    file.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(bmpFileHeader));
    BITMAPINFOHEADER bmpInfoHeader;
    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
    int ys, ye, inc;
    if (bmpInfoHeader.biHeight < 0) {
        height = -bmpInfoHeader.biHeight;
        ys = 0;
        ye = height;
        inc = 1;
    }
    else {
        height = bmpInfoHeader.biHeight;
        ys = height - 1;
        ye = -1;
        inc = -1;
    }

    width = bmpInfoHeader.biWidth;
    assert(bmpInfoHeader.biBitCount == 24 || bmpInfoHeader.biBitCount == 32);
    assert(bmpInfoHeader.biCompression == BI_RGB);
    pixels.resize(width * height);
    file.seekg(bmpFileHeader.bfOffBits);
    int padding = (4 - (width * 3) % 4) % 4;
    for (int lig = ys; lig != ye; lig += inc) {
        for (int col = 0; col < width; col++) {
            PutPixel(col, lig, Color(file.get(), file.get(), file.get()));
            if (bmpInfoHeader.biBitCount == 32) {
                file.seekg(1, std::ios::cur);
            }
        }
        if (bmpInfoHeader.biBitCount == 24) {
            file.seekg(padding, std::ios::cur);
        }


    }


}

void Surface::PutPixel(int x, int y, Color c)
{
    pixels[y * width + x] = c;
}



Color Surface::GetPixel(int x, int y) const
{
    return pixels[y * width + x];
}

int Surface::GetWidth() const
{
    return width;
}

int Surface::GetHeight() const
{
    return height;
}
RectI Surface::GetRect() const {
    return { 0,height,0,width };
}
const Color* Surface::Data() const {
    return pixels.data();
}