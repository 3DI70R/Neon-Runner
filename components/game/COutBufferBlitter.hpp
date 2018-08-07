#pragma once
#include "Types.hpp"
#include "TRGBColor.hpp"
#include "CHal.hpp"

extern RGBColor defaultBgGradient[];
extern RGBColor defaultFgGradient[];
extern RGBColor defaultObjPalette[];

class COutBufferBlitter {

    pcolor* bgBuffer;
    pcolor* fgBuffer;
    pcolor* objBuffer;
    CHal* hal;

    RGBColor* bgGradient;
    RGBColor* fgGradient;
    RGBColor* objPalette;

    public:
        COutBufferBlitter(pcolor* bgBuffer, pcolor* fgBuffer, pcolor* objBuffer, CHal* hal);

        inline void setBgGradient(RGBColor* gradient) {
            bgGradient = gradient;
        }

        inline void setFgGradient(RGBColor* gradient) {
            fgGradient = gradient;
        }

        inline void setObjPalette(RGBColor* palette) {
            objPalette = palette;
        }

        void blit();
};