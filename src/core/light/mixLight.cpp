#include "mixLight.h"

mix::core::light::mixLight::mixLight () : mixLight (light_type::directional, vec3 (1))
{
}

mix::core::light::mixLight::mixLight (light_type type) : mixLight (type, vec3 (1))
{
}

mix::core::light::mixLight::mixLight (light_type type, vec3 color)
: _type{ type }, _intensity{ 1 }, _color{ color }, mixEntity ()
{
}

mix::core::light::light_type mix::core::light::mixLight::get_type () const
{
    return _type;
}

float mix::core::light::mixLight::get_intensity () const
{
    return _intensity;
}

vec3 mix::core::light::mixLight::get_color () const
{
    return _color;
}

void mix::core::light::mixLight::set_type (light_type t)
{
    _type = t;
}

void mix::core::light::mixLight::set_intensity (float f)
{
    _intensity = f;
}

void mix::core::light::mixLight::set_color (vec3 color)
{
    _color = color;
}
