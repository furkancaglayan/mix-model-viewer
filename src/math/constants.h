#pragma once
#include "vec.h"

constexpr float PI = 3.14159265358979323846f;
constexpr float DegreesToRadians = PI / 180.0f;

static constexpr float degrees_to_radians (float d)
{
    return d * DegreesToRadians;
}
