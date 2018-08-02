#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "types.h"

void transform_set_translation(vector2 translation);
void transform_set_rotation(float rotation);
void transform_set_scale(float scale);

vector2 transform_apply(vector2 point, float depth);

#endif