#ifndef CBUFFERBLUREFFECT_H
#define CBUFFERBLUREFFECT_H
#include "Types.hpp"

class CBufferBlurEffect {
    private:
        int rAcc;
        int gAcc;
        int bAcc;
        int accumulatorSize;

    public:
        void blur(color* buffer, int width, int height, int radius);

        color getAccumulatorColor();
        void clearAccumulator();
        void pushAccumulator(color c);
        void popAccumulator(color c);

        void processHorizontal(color* buffer, int width, int height, int radius);
        void processVertical(color* buffer, int width, int height, int radius);
};

#endif