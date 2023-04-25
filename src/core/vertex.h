#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>
namespace mix
{
    namespace assetsystem
    {
        struct vertex
        {
            public:

            vertex (glm::vec3 position, glm::vec3 normal, glm::vec3 uv, glm::vec3 t, glm::vec3 b)
            : _position{ position }, _normal{ normal }, _tex_coords{ uv }, _tangent{ t }, _bitangent{ b }
            {
            }
            glm::vec3 _position;
            glm::vec3 _normal;
            glm::vec3 _tex_coords;
            glm::vec3 _tangent;
            glm::vec3 _bitangent;
        };
    } // namespace assetsystem
} // namespace mix
