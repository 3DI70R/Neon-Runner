#ifndef CDRAWABLE_H
#define CDRAWABLE_H
#include "Types.hpp"

class CDrawable {
    public: 
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual color getColor(int x, int y) = 0;
        virtual pixel_attr getAttr(int x, int y) = 0;
};


#endif