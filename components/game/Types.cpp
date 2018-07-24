#include "math.h"
#include <algorithm>
#include "Types.hpp"

float CPoint::squaredDistanceTo(CPoint* point) {
    coord xDiff = (x - point->x);
    coord yDiff = (y - point->y);
    return xDiff * xDiff + yDiff * yDiff;
}

float CPoint::distanceTo(CPoint* point) {
    return sqrt(squaredDistanceTo(point));
}

CRect::CRect() {
    // noop
}

CRect::CRect(coord width, coord height) {
    max.x = width;
    max.y = height;
}

CRect::CRect(coord xMin, coord yMin, coord xMax, coord yMax) {
    min.x = xMin;
    min.y = yMin;
    max.x = xMax;
    max.y = yMax;
}

coord CRect::getWidth() {
    return max.x - min.x;
}

coord CRect::getHeight() {
    return max.y - min.y;
}

void CRect::move(coord x, coord y) {
    min.x += x;
    min.y += y;
    max.x += x;
    max.y += y;
}

void CRect::normalize() {
    coord temp;

    if(min.x > max.x) {
        temp = max.x;
        max.x = min.x;
        min.x = temp;
    }

    if(min.y > max.y) {
        temp = max.y;
        max.y = min.y;
        min.y = temp;
    }
}

CRect CRect::intersectWith(CRect* rect) {
    CRect i;
    i.min.x = std::max(min.x, rect->min.x);
    i.min.y = std::max(min.y, rect->min.y);
    i.max.x = std::min(max.x, rect->max.x);
    i.max.y = std::min(max.y, rect->max.y);
    return i;
}