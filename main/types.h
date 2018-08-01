#ifndef TYPES_H
#define TYPES_H

typedef unsigned char byte;
typedef byte BOOL;

#define true 1
#define false 0

typedef union {
    struct { float x, y; };
    float raw[2];
} vector2;

typedef union {
    struct { byte r, g, b; };
    byte raw[3];
} color;

typedef vector2 bezier[4];

typedef struct {
    vector2 position;
    float angle;
    float width;
} segment;

#endif