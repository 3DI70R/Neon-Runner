#ifndef UTILS_H
#define UTILS_H

inline int get2DArrayOffset(int width, int x, int y) {
    return x + y * width;
}

#endif