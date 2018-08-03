#ifndef PIPE_H
#define PIPE_H
#include "types.h"

#define PIPE_SEGMENT_TESSELATION_COUNT 16

typedef struct {
    segment segments[PIPE_SEGMENT_TESSELATION_COUNT];
    bezier* bezier;
    float start_width;
    float end_width;
} pipe;

pipe pipe_create_from_bezier(bezier* bezier, float start_width, float end_width);

void pipe_draw(pipe* pipe);

#endif