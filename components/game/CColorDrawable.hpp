#ifndef CCOLOR_DRAWABLE_H
#define CCOLOR_DRAWABLE_H
#include "Types.hpp"
#include "CDrawable.hpp"

class CColorDrawable : public CDrawable {

    private:
        int width;
        int height;
        color fillColor;
        pixel_attr attr;

    public:
        CColorDrawable(int width, int height, color fillColor, pixel_attr attr);
        virtual int getWidth();
        virtual int getHeight();
        virtual color getColor(int x, int y);
        virtual pixel_attr getAttr(int x, int y);
};

#endif