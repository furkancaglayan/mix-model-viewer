#pragma once
#include "vec.h"
#include <memory>
#include <string>
namespace mix
{
    namespace math
    {
        struct vertex
        {
            public:

            vertex (vec3 position, vec3 normal, vec3 uv, vec3 t, vec3 b)
            : _position{ position }, _normal{ normal }, _tex_coords{ uv }, _tangent{ t }, _bitangent{ b }
            {
            }

            vertex (vec3 position)
            : _position{ position }, _normal{ vec3 (0) }, _tex_coords{ vec2 (0) }, _tangent{ vec3 (0) }, _bitangent{ vec3 (0) }
            {
            }

            vec3 _position;
            vec3 _normal;
            vec2 _tex_coords;
            vec3 _tangent;
            vec3 _bitangent;
        };
    } // namespace math
} // namespace mix
