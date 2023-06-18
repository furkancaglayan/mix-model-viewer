#include "color.h"

mix::math::color::color () : color (0.0f, 0.0f, 0.0f)
{
}

mix::math::color::color (float r, float g, float b) : _color{ r, g, b, 1.0f }
{
}

mix::math::color::color (float r, float g, float b, float a) : color (vec4(r, g, b, a))
{
}

mix::math::color::color (vec4 col) : _color{ col }
{
}

mix::math::color::color (vec3 col) : color (vec4(col.x, col.y, col.z, 1))
{
}

mix::math::color::color (int r, int g, int b)
: color (vec3 (static_cast<float> (r) / 255, static_cast<float> (g) / 255, static_cast<float> (b) / 255))
{
}

mix::math::color::color (int r, int g, int b, int a)
: color (vec4 (static_cast<float> (r) / 255, static_cast<float> (g) / 255, static_cast<float> (b) / 255, static_cast<float> (a) / 255))
{
}

mix::math::color::color (unsigned u) : color ((int)(u & 0xFF000000) >> 24, (u & 0xFF000000) >> 16, (u & 0xFF000000) >> 8)
{
}

unsigned mix::math::color::to_uint ()
{
    uint8_t r = (uint8_t) (_color.x * 255);
    uint8_t g = (uint8_t) (_color.y * 255);
    uint8_t b = (uint8_t) (_color.z * 255);
    uint8_t a = (uint8_t) (_color.w * 255);
    return (unsigned)((r << 24) | (g << 16) | (b << 8) | (a << 0));
}

vec4 mix::math::color::get_value ()
{
    return _color;
}

mix::math::color mix::math::color::from_uint (unsigned u)
{
    return color (u);
}
