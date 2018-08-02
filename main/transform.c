#include "transform.h"

vector2 transform_translation;
float transform_rotation;

void transform_set_translation(vector2 translation)
{
    transform_translation = translation;
}

void transform_set_rotation(float angle)
{
    transform_rotation = angle;
}

vector2 transform_apply(vector2 point, float depth)
{
    vector2 r;

    // TODO: correct transformations?
    r.x = (point.x - transform_translation.x) - 40;
    r.y = (point.y - transform_translation.y) - 32;
    r.x = r.x * depth + 40;
    r.y = r.y * depth + 32;

    return r;
}