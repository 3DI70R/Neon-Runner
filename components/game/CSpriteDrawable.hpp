#ifndef CSPRITEDRAWABLE_H
#define CSPRITEDRAWABLE_H
#include "CDrawable.hpp"
#include "Types.hpp"

class CSpriteDrawable : public CDrawable {

    static const int paletteIndexMask = 0x1F;
    static const int attributeMask = 0xE0;
    
    private:
        byte width;
        byte height;
        pixel_attr* graphics;
        color* palette;

    public:
        CSpriteDrawable(byte width, byte height, pixel_attr* graphics, color* palette);
        virtual int getWidth();
        virtual int getHeight();
        virtual color getColor(int x, int y);
        virtual pixel_attr getAttr(int x, int y);
};


#endif