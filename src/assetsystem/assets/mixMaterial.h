#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "mixTexture.h"
#include "mixShader_program.h"
#include "../../math/vec.h"

namespace mix
{
    namespace assetsystem
    {
        class mixMaterial : public mix::assetsystem::mixAsset_item
        {
            public:

            mixMaterial (const mix::platform::mixAsset_path& path, std::shared_ptr<mix::assetsystem::mixShader_program> shader);
            mixMaterial (const std::string& path, std::shared_ptr<mix::assetsystem::mixShader_program> shader);
            ~mixMaterial ();

            void set_shader (std::shared_ptr<mix::assetsystem::mixShader_program> shader);
            void set_color (vec4 color);
            void set_color (vec3 color);
            void set_opacity (float a);
            unsigned apply () const;
            mix::assetsystem::mixShader_program* get_shader () const;
            void set_texture (mix::texture::texture_type type, std::shared_ptr<mix::assetsystem::mixTexture> texture);
            vec4 get_color () const;
            private:

            vec4 _color;
            float _ambient{ 0.33f };
            float _specular{ 0.33f };
            float _shininess{ 0.33f };
            std::weak_ptr<mix::assetsystem::mixShader_program> _shader;
            std::unordered_map<mix::texture::texture_type, std::weak_ptr<mix::assetsystem::mixTexture>> _textures;
        };
    } // namespace assetsystem
} // namespace mix
