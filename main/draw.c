#include "draw.h"
#include <stdlib.h>
#include <string.h>

byte* current_buffer;
int current_buffer_width;
int current_buffer_height;

void draw_clear(byte color) 
{
    memset(current_buffer, color, sizeof(byte) * current_buffer_width * current_buffer_height);
}

void draw_set_buffer(int width, int height, byte* data) 
{
    current_buffer = data;
    current_buffer_width = width;
    current_buffer_height = height;
}

void draw_pixel(int x, int y, byte color) 
{
    if(x >= 0 && x < current_buffer_width && y >= 0 && y < current_buffer_height) 
    {
        current_buffer[x + y * current_buffer_width] = color;
    }
}

int draw_line_pattern(int x0, int y0, int x1, int y1, byte* pattern, int pattern_size, int pattern_offset, BOOL repeat) 
{
    int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2;
    int pattern_index = pattern_offset;
 
    while(1) 
    { 
        draw_pixel(x0, y0, pattern[pattern_index++]);

        if(pattern_index >= pattern_size) 
        {
            if(repeat) 
            {
                pattern_index = 0;
            }
            else 
            {
                break;
            }
        }

        if (x0 == x1 && y0 == y1) 
        {
            break;
        }

        e2 = 2 * err;

        if (e2 >= dy) 
        {
            err += dy; 
            x0 += sx; 
        }

        if (e2 <= dx)
        { 
            err += dx; 
            y0 += sy; 
        }
    }

    return pattern_index;
}

void draw_line (int x0, int y0, int x1, int y1, byte color)
{
    draw_line_pattern(x0, y0, x1, y1, &color, 1, 0, true);
}