#include "COutBufferBlitter.hpp"

RGBColor defaultBgGradient[] =
{
    RGBColor(255, 206, 13),
    RGBColor(82, 244, 156),
    RGBColor(255, 55, 170),
    RGBColor(106, 154, 235)
};

RGBColor defaultFgGradient[] =
{
    RGBColor(255, 0, 0),
    RGBColor(255, 0, 128),
    RGBColor(0, 0, 255),
    RGBColor(0, 128, 255)
};

RGBColor defaultObjPalette[] =
{
    RGBColor(0, 0, 0),       // transparent
    RGBColor(255, 255, 255), // player FG
    RGBColor(232, 232, 232), // player BG
};

COutBufferBlitter::COutBufferBlitter(pcolor* bgBuffer, pcolor* fgBuffer, pcolor* objBuffer, CHal* hal) {
    this->bgBuffer = bgBuffer;
    this->fgBuffer = fgBuffer;
    this->objBuffer = objBuffer;
    this->hal = hal;

    setBgGradient(defaultBgGradient);
    setFgGradient(defaultFgGradient);
    setObjPalette(defaultObjPalette);
}

void COutBufferBlitter::blit() {
    hal->clearScreen();

    int width = hal->getScreenWidth();
    int height = hal->getScreenHeight();

    byte* bg = this->bgBuffer;
    byte* fg = this->fgBuffer;
    byte* obj = this->objBuffer;

    RGBColor color(0, 0, 0);
    RGBColor bgLeft;
    RGBColor bgRight;
    RGBColor fgLeft;
    RGBColor fgRight;

    // TODO: further optimize this part

    for(int y = 0; y < height; y++) {

        float t = y / (height - 1.f);
        bgLeft = RGBColor::lerp(bgGradient[0], bgGradient[2], t);
        bgRight = RGBColor::lerp(bgGradient[1], bgGradient[3], t);
        fgLeft = RGBColor::lerp(fgGradient[0], fgGradient[2], t);
        fgRight = RGBColor::lerp(fgGradient[1], fgGradient[3], t);

        for(int x = 0; x < width; x++) {
            byte c = *obj;
            if(c != 0) {
                color = objPalette[c];
                hal->drawPixel(x, y, color.r, color.g, color.b);
            } else {
                c = *fg;
                if(c != 0) {
                    color.asLerp(fgLeft, fgRight, x / (width - 1.0f));
                    color.scale(c / 255.0f);
                    hal->drawPixel(x, y, color.r, color.g, color.b);
                } else {
                    c = *bg;
                    if(c != 0) {
                        color.asLerp(bgLeft, bgRight, x / (width - 1.0f));
                        color.scale(c / 255.0f);
                        hal->drawPixel(x, y, color.r, color.g, color.b);
                    }
                }
            }

            bg++;
            fg++;
            obj++;
        }
    }
}