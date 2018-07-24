#ifndef CORE_TYPES
#define CORE_TYPES

#define ATTR_TRANSPARENT 0x20
#define ATTR_OCCLUSION 0x40
#define ATTR_EMISSIVE 0x80

#define BTN_RIGHT 1
#define BTN_LEFT 2
#define BTN_UP 4
#define BTN_DOWN 8
#define BTN_START 16
#define BTN_SELECT 32
#define BTN_A 64
#define BTN_B 128
#define BTN_C 256

typedef unsigned char byte;
typedef byte sprite_pixel;

typedef byte pixel_attr;
typedef unsigned short color;
typedef int coord;

typedef void (*imageOutputFunc)(const short unsigned int* buffer);
typedef void (*soundOutputFunc)(unsigned char *buf, int len);
typedef unsigned int (*controlsInputFunc)();

struct CPoint {
    coord x;
    coord y;

    float squaredDistanceTo(CPoint* point);
    inline float distanceTo(CPoint* point);
};

struct CRect {
    CPoint min;
    CPoint max;

    CRect();
    CRect(coord width, coord height);
    CRect(coord xMin, coord yMin, coord xMax, coord yMax);

    coord getWidth();
    coord getHeight();
    void move(coord x, coord y);

    void normalize();

    CRect intersectWith(CRect* rect);
};

#endif