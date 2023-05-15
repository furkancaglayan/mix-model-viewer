#include "mixCamera.h"

mix::core::mixCamera::mixCamera () : mixEntity ()
{
}

mat4 mix::core::mixCamera::get_view_mat () const
{
    auto at = _transform->get_position ();
    auto up = _transform->up ();
    return lookat (at, at + _transform->forward (), up);
}

mat4 mix::core::mixCamera::get_projection_mat () const
{

    if (_projection == projection_mode::perspective)
    {
        return perspective (_fov, _aspect, _near, _far);
    }
    else
    {
        return ortho (-5, 5, -5, 5);
    }
}

void mix::core::mixCamera::change_projection (projection_mode p)
{
    _projection = p;
}

void mix::core::mixCamera::update ()
{
    mix::core::mixEntity::update ();

}

void mix::core::mixCamera::debug_input (vec3 v)
{
    _transform->translate (v * 0.015f);
}
