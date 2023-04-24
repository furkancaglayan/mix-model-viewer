#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace mix
{
    namespace assetsystem
    {
        struct vertex 
        {
            glm::vec3 _position;
            glm::vec3 _normal;
            glm::vec2 _tex_coords;
            glm::vec3 _tangent;
            glm::vec3 _bitangent;
        };
    } // namespace assetsystem
} // namespace mix
