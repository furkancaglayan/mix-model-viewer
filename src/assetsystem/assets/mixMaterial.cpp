#include "mixMaterial.h"

mix::assetsystem::mixMaterial::mixMaterial (std::shared_ptr<mix::assetsystem::mixShader_program> shader)
: _color{ vec4 (1.0f, 1.0f, 1.0f, 1.0f) }
{
    _shader = shader;
}

mix::assetsystem::mixMaterial::~mixMaterial ()
{
}

void mix::assetsystem::mixMaterial::set_shader (std::shared_ptr<mix::assetsystem::mixShader_program> shader)
{
    _shader = shader;
}

mix::assetsystem::mixShader_program* mix::assetsystem::mixMaterial::get_shader () const
{
    if (_shader.expired ())
    {
        return nullptr;
    }

    return _shader.lock ().get ();
}

void mix::assetsystem::mixMaterial::set_color (vec4 color)
{
    _color = color;
}

void mix::assetsystem::mixMaterial::set_color (vec3 color)
{
    //TODO: operator
    _color[0] = color[0];
    _color[1] = color[1];
    _color[2] = color[2];
}

void mix::assetsystem::mixMaterial::set_opacity (float a)
{
    _color[3] = a;
}

void mix::assetsystem::mixMaterial::apply () const
{
    if (_shader.expired ())
    {
        return;
    }

    _shader.lock ()->use ();
    _shader.lock ()->set_vec4 ("_color", _color);
    _shader.lock ()->set_1f ("_ambient", _ambient);
    _shader.lock ()->set_1f ("_specular", _specular);
    _shader.lock ()->set_1f ("_shininess", _shininess);
}
