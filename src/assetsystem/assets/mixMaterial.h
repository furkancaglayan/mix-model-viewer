#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "mixTexture.h"
#include "mixShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mix
{
    namespace assetsystem
    {
        class mixMaterial 
        {
            public:

            mixMaterial (mixShader* shader);
            ~mixMaterial ();

            void set_shader (std::shared_ptr<mix::assetsystem::mixShader> shader);
            mix::assetsystem::mixShader* get_shader () const;
            void set_color (glm::vec3 color);
            glm::vec4 get_color () const;
            private:

            glm::vec4 _color;
            std::weak_ptr<mix::assetsystem::mixShader> _shader;
            std::unordered_map<mix::texture::texture_type, std::weak_ptr<mix::assetsystem::mixTexture>> _textures;
        };
    } // namespace assetsystem
} // namespace mix
