#include "mixCamera.h"

mat4 mix::core::mixCamera::get_view_mat () const
{
    return lookat (_eye, _at, _up);
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

void mix::core::mixCamera::refresh ()
{
    _forward.x = cos (degrees_to_radians (_yaw)) * cos (DegreesToRadians * (_pitch));
    _forward.y = sin (degrees_to_radians (_pitch));
    _forward.z = sin (degrees_to_radians (_yaw)) * cos (DegreesToRadians * (_pitch));
    _forward = normalize (_forward);


    _right.x = cos (degrees_to_radians (_yaw + 90)) * cos (degrees_to_radians (_pitch + 90));
    _right.y = 0;
    _right.z = sin (degrees_to_radians (_yaw + 90)) * cos (degrees_to_radians (_pitch + 90));
    _right = normalize (_right);

    _up = cross (_right, _forward);
    _up = normalize (-_up);

    _at = _eye + vec4(_forward.x, _forward.y, _forward.z, 0.0f);
    _at.w = 1;
}
