#include "Types.hpp"

class CLevelTile {

    public:
        const byte width = 8;
        const byte height = 8;
        light lightLevel;

        pindex* graphics;
        light* lights;

    public:
        CLevelTile();
        ~CLevelTile();

        virtual void onTick() = 0;
        virtual void onDraw() = 0;
        virtual void onEntityStep() = 0;
        virtual void onEntityStand() = 0;

        virtual void onRenderEnable() = 0;
        virtual void onRenderDisable() = 0;
};