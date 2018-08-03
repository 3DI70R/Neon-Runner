#include "draw.h"
#include <stdlib.h>
#include <string.h>

byte* current_buffer;
int current_buffer_width;
int current_buffer_height;

void draw_fill(byte color) 
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

void draw_fill_pattern(byte* pattern, int width, int height, int x_offset, int y_offset)
{
    int line = y_offset;

    for(int y = 0; y < current_buffer_height; y++) 
    {
        byte* pattern_line = &pattern[line * width];

        for(int x = x_offset; x < current_buffer_width; x += width) 
        {
            memcpy(&current_buffer[x + y * current_buffer_width], 
                   pattern_line, width * sizeof(byte));
        }

        line++;

        if(line >= height)
        {
            line = 0;
        }
    }
}

// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

void draw_fill_bottom_triangle(vector2 v1, vector2 v2, vector2 v3, byte color)
{
    float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
    float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++)
    {
        draw_line((int) curx1, scanlineY, (int)curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void draw_fill_top_triangle(vector2 v1, vector2 v2, vector2 v3, byte color)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;

    for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
    {
        draw_line((int)curx1, scanlineY, (int)curx2, scanlineY, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

int vector2_sort( const void * v1, const void * v2 ) 
{
    return (int) ((*(vector2*) v1).y - (*(vector2*) v2).y);
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, byte color) 
{
    vector2 vertices[] = 
    {
        { .x = x0, .y = y0 },
        { .x = x1, .y = y1 },
        { .x = x2, .y = y2 }
    };

    qsort(vertices, 3, sizeof(vector2), vector2_sort);

    if (vertices[1].y == vertices[2].y)
    {
        draw_fill_bottom_triangle(vertices[0], vertices[1], vertices[2], color);
    }
    else if (vertices[0].y == vertices[1].y)
    {
        draw_fill_top_triangle(vertices[0], vertices[1], vertices[2], color);
    } 
    else
    {
        vector2 v4 =
        { 
            .y = vertices[1].y,
            .x = (int)(vertices[0].x + ((float)(vertices[1].y - vertices[0].y) / 
                 (float)(vertices[2].y - vertices[0].y)) * (vertices[2].x - vertices[0].x))
        };

        draw_fill_bottom_triangle(vertices[0], vertices[1], v4, color);
        draw_fill_top_triangle(vertices[1], v4, vertices[2], color);
    }
}