#include "mixTransform.h"
#include <iostream>

void mix::core::mixTransform::set_position (vec3 v)
{
    _position = v;
    _is_dirty = true;
}

void mix::core::mixTransform::set_local_position (vec3 v)
{
    _local_position = v;
    _is_dirty = true;
}

void mix::core::mixTransform::set_rotation (vec3 v)
{
    _rotation = v;
    _is_dirty = true;
}

void mix::core::mixTransform::set_scale (vec3 v)
{
    _scale = v;
    _is_dirty = true;
}

void mix::core::mixTransform::translate (vec3 v)
{
    _position += v;
    _is_dirty = true;
}

void mix::core::mixTransform::scale (vec3 v)
{
}

void mix::core::mixTransform::look_at (const vec3& pos)
{
    auto d = normalize (-pos + _position);
    _rotation.y =radians_to_degrees ((float) atan (d.x / (-d.y)));
    _rotation.x = radians_to_degrees ((float) atan (pow (d.x, 2) + pow (d.y, 2)));
    _is_dirty = true;
    update ();
}


void mix::core::mixTransform::rotate_around (float x, float y, float z)
{
    _rotation.x += x;
    _rotation.y += y;
    _rotation.z += z;
    _is_dirty = true;
}

mat4 mix::core::mixTransform::get_model_mat () const
{
    mat4 m (1.0f);
    m = rotate (m, _rotation.x, transform::right);
    m = rotate (m, _rotation.y, transform::up);
    m = rotate (m, _rotation.z, transform::forward);
    m = glm::translate (m, _position);
    return m;
}

mix::core::mixTransform::mixTransform () : mixTransform (vec3 (0), vec3 (0), vec3 (1))
{
}

mix::core::mixTransform::mixTransform (vec3 pos) : mixTransform (pos, vec3 (0), vec3 (1))
{
}

mix::core::mixTransform::mixTransform (vec3 pos, vec3 rot) : mixTransform (pos, rot, vec3 (1))
{
}

mix::core::mixTransform::mixTransform (vec3 pos, vec3 rot, vec3 scale)
: _position{ pos }, _local_position{ 0 }, _rotation{ rot }, _scale{ scale }, _is_dirty{ true }
{
    update ();
}

mix::core::mixTransform::~mixTransform ()
{
}

void mix::core::mixTransform::update ()
{
    if (_is_dirty)
    {
        update_vectors ();
        _is_dirty = false;
    }
}

void mix::core::mixTransform::update_vectors ()
{
    auto _yaw = yaw ();
    auto _pitch = pitch ();

    _forward.x = cos (degrees_to_radians (_yaw)) * cos (degrees_to_radians (_pitch));
    _forward.y = sin (degrees_to_radians (_pitch));
    _forward.z = sin (degrees_to_radians (_yaw)) * cos (degrees_to_radians (_pitch));
    _forward = normalize (_forward);

    _right = normalize (cross (_forward, transform::up));
    _up = normalize (cross (_right, _forward));
}

