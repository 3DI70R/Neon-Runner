#pragma once
#include "Types.hpp"
#include "TRGBColor.hpp"
#include "CHal.hpp"

extern RGBColor defaultBgGradient[];
extern RGBColor defaultFgGradient[];
extern RGBColor defaultObjPalette[];

typedef bool (*StencilTestFunc)(byte, byte);

class COutBufferBlitter {

    pcolor* bgBuffer;
    pcolor* fgBuffer;
    pcolor* objBuffer;
    CHal* hal;
    StencilTestFunc stencil;

    RGBColor* bgGradient;
    RGBColor* fgGradient;
    RGBColor* objPalette;

    public:
        COutBufferBlitter(pcolor* bgBuffer, pcolor* fgBuffer, pcolor* objBuffer, CHal* hal);

        void setStencil(StencilTestFunc stencil) {
            if(stencil == nullptr) {
                this->stencil = [](byte x, byte y) { return false; };
            } else {
                this->stencil = stencil;
            }
        }

        void setBgGradient(RGBColor* gradient) {
            bgGradient = gradient;
        }

        void setFgGradient(RGBColor* gradient) {
            fgGradient = gradient;
        }

        void setObjPalette(RGBColor* palette) {
            objPalette = palette;
        }

        void blit();
};