#pragma once
#include <stdbool.h>

#define BTN_RIGHT (1<<0)
#define BTN_LEFT (1<<1)
#define BTN_UP (1<<2)
#define BTN_DOWN (1<<3)
#define BTN_START (1<<4)
#define BTN_SELECT (1<<5)
#define BTN_A (1<<6)
#define BTN_B (1<<7)

#define COLOR_PLAYER_FG 1
#define COLOR_PLAYER_BG 2
#define COLOR_GLITCH_1 3
#define COLOR_GLITCH_2 4
#define COLOR_GLITCH_3 5
#define COLOR_GLITCH_4 6

typedef unsigned char byte;

// Palette color index
typedef byte pcolor;