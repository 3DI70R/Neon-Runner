#ifndef TYPES_H
#define TYPES_H

typedef union {
    struct { float x, y; };
    float raw[2];
} vector2;

typedef vector2 bezier[4];

typedef struct {
    vector2 position;
    float angle;
    float width;
} segment;

#endif