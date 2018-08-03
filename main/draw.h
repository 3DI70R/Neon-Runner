#ifndef DRAW_H
#define DRAW_H
#include "types.h"

#define MAX_LAYERS 3
#define LAYER_BG 0
#define LAYER_FG 1
#define LAYER_OBJ 2

void draw_set_layer_params(int layer_index, int width, int height, byte* data);
void draw_switch_layer(int layer_id);

void draw_pixel(int x, int y, byte color);
void draw_line (int x0, int y0, int x1, int y1, byte color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, byte color);

int draw_line_pattern (int x0, int y0, int x1, int y1, byte* pattern, int pattern_size, int pattern_offset, BOOL repeat);
void draw_fill(byte color);
void draw_fill_pattern(byte* pattern, int width, int height, int x_offset, int y_offset);
#endif