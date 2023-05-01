#pragma once
#include <memory>
#include <string>
#include "vec.h"
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
            vec3 _position;
            vec3 _normal;
            vec3 _tex_coords;
            vec3 _tangent;
            vec3 _bitangent;
        };
    } // namespace assetsystem
} // namespace mix
