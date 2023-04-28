#include "mixMaterial.h"

mix::assetsystem::mixMaterial::mixMaterial (std::shared_ptr<mix::assetsystem::mixShader_program> shader)
: _color{ glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f) }
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

void mix::assetsystem::mixMaterial::set_color (glm::vec4 color)
{
    _color = color;
}

void mix::assetsystem::mixMaterial::set_color (glm::vec3 color)
{
    _color.x = color.x;
    _color.y = color.y;
    _color.z = color.z;
}

void mix::assetsystem::mixMaterial::set_opacity (float a)
{
    _color.w = a;
}

void mix::assetsystem::mixMaterial::apply () const
{
    if (_shader.expired ())
    {
        return;
    }

    _shader.lock ()->use ();
    _shader.lock ()->set_vec4 (1, _color);
}
