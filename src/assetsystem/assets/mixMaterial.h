#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "mixTexture.h"
#include "mixShader_program.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mix
{
    namespace assetsystem
    {
        class mixMaterial 
        {
            public:

            mixMaterial (std::shared_ptr<mix::assetsystem::mixShader_program> shader);
            ~mixMaterial ();

            void set_shader (std::shared_ptr<mix::assetsystem::mixShader_program> shader);
            void set_color (glm::vec4 color);
            void set_color (glm::vec3 color);
            void set_opacity (float a);
            void apply () const;
            mix::assetsystem::mixShader_program* get_shader () const;

            inline glm::vec4 get_color () const
            {
                return _color;
            }
            private:

            glm::vec4 _color;
            std::weak_ptr<mix::assetsystem::mixShader_program> _shader;
            std::unordered_map<mix::texture::texture_type, std::weak_ptr<mix::assetsystem::mixTexture>> _textures;
        };
    } // namespace assetsystem
} // namespace mix
