#include "transform.h"
#include "mathg.h"

vector2 transform_translation;
float transform_rotation;
float transform_scale;

void transform_set_translation(vector2 translation)
{
    transform_translation = translation;
}

void transform_set_rotation(float angle)
{
    transform_rotation = angle;
}

void transform_set_scale(float scale)
{
    transform_scale = scale;
}

vector2 transform_apply(vector2 point, float depth)
{
    vector2 r;

    // TODO: correct transformations?
    r.x = point.x - transform_translation.x - 40;
    r.y = point.y - transform_translation.y - 32;
    r.x = r.x * depth * transform_scale;
    r.y = r.y * depth * transform_scale;
    r = vector2_rotate(r, transform_rotation);
    r.x += 40;
    r.y += 32;

    return r;
}