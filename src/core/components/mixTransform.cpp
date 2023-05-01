#include "mixTransform.h"
#include <iostream>

void mix::components::mixTransform::set_position (vec3 v)
{
    _position = v;
    _is_dirty = true;
}

void mix::components::mixTransform::set_local_position (vec3 v)
{
    _local_position = v;
    _is_dirty = true;
}

void mix::components::mixTransform::set_rotation (vec3 v)
{
    _rotation = v;
    _is_dirty = true;
}

void mix::components::mixTransform::set_scale (vec3 v)
{
    _scale = v;
    _is_dirty = true;
}

void mix::components::mixTransform::translate (vec3 v)
{
    _position += v;
    _is_dirty = true;
}

void mix::components::mixTransform::scale (vec3 v)
{
}

void mix::components::mixTransform::rotate (vec3 v)
{
}

mat4 mix::components::mixTransform::get_model_mat () const
{
    return mat4 (1, 0, 0, _position.x, 0, 1, 0, _position.y, 0, 0, 1, _position.z, 0, 0, 0, 1);
}

mix::components::mixTransform::mixTransform () : mixTransform (vec3 (0), vec3 (0), vec3 (1))
{
}

mix::components::mixTransform::mixTransform (vec3 pos) : mixTransform (pos, vec3 (0), vec3 (1))
{
}

mix::components::mixTransform::mixTransform (vec3 pos, vec3 rot) : mixTransform (pos, rot, vec3 (1))
{
}

mix::components::mixTransform::mixTransform (vec3 pos, vec3 rot, vec3 scale)
: _position{ pos }, _local_position{ 0 }, _rotation{ rot }, _scale{ scale }, _is_dirty{ true }
{
    update ();
}

mix::components::mixTransform::~mixTransform ()
{
}

void mix::components::mixTransform::update ()
{
    if (_is_dirty)
    {
        update_vectors ();
        _is_dirty = false;
    }
}

void mix::components::mixTransform::update_vectors ()
{
    auto _yaw = yaw ();
    auto _pitch = pitch ();

    _forward.x = cos (degrees_to_radians (_yaw)) * cos (degrees_to_radians (_pitch));
    _forward.y = sin (degrees_to_radians (_pitch));
    _forward.z = sin (degrees_to_radians (_yaw)) * cos (degrees_to_radians (_pitch));
    _forward = normalize (_forward);

    _right = normalize (cross (_forward, transform::up));
    _up = normalize (cross (_right, _forward));
    std::cout << _position.x << "," << _position.y
              << "," << _position.z << std::endl;
}

