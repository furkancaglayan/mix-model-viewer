#pragma once
#include "mixAsset_item.h"
#include <memory>
#include <string>

namespace mix
{
    class texture
    {
        public:

        enum class texture_type : uint8_t
        {
            diffuse = 0,
            normal = 2,
            specular = 4,
            height = 8
        };

        enum class texture_wrapping : int
        {
            repeat = GL_REPEAT,
            mirrored_repeat = GL_MIRRORED_REPEAT,
            clamp = GL_CLAMP,
            clamp_to_edge = GL_CLAMP_TO_EDGE,
            clamp_to_border = GL_CLAMP_TO_BORDER,
        };

        enum class texture_filtering : int
        {
            /// <summary>
            /// GL_NEAREST is the default texture filtering method of OpenGL. When set to GL_NEAREST, OpenGL selects the
            /// texel that center is closest. Also known as point filtering.
            /// </summary>
            nearest = GL_NEAREST,
            /// <summary>
            /// GL_LINEAR takes an interpolated value from the texture coordinate's neighboring texels, approximating a
            /// color between the texels. The smaller the distance from the texture coordinate to a texel's center, the
            /// more that texel's color contributes to the sampled color. Also known as bi-linear filtering.
            /// </summary>
            linear = GL_LINEAR,
        };

        enum class mipmap_method : int
        {
            repeat = GL_NEAREST_MIPMAP_NEAREST,
            mirrored_repeat = GL_LINEAR_MIPMAP_NEAREST,
            clamp_to_edge = GL_LINEAR_MIPMAP_NEAREST,
            clamp_to_border = GL_LINEAR_MIPMAP_LINEAR,
        };
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        static std::string get_texture_target (texture_type type)
        {
            return std::string ("texture") + std::to_string (static_cast<int> (type));
        }
        texture () = delete;
        ~texture () = delete;
    };

    namespace assetsystem
    {
        class mixTexture : public mix::assetsystem::mixAsset_item
        {
            public:

            mixTexture (const mix::platform::mixAsset_path& path, texture::texture_type type = texture::texture_type::diffuse);
            ~mixTexture ();

            inline const mix::texture::texture_type get_texture_type () const
            {
                return _type;
            }

            void set_wrapping (texture::texture_wrapping wrapping);
            void set_filtering (texture::texture_filtering filtering_min, texture::texture_filtering filtering_mag);
            void bind () const;
            void change_type (mix::texture::texture_type t);

            private:

            void initialize (const mix::platform::mixAsset_path& path);
            unsigned int _id;
            texture::texture_type _type{ texture::texture_type::diffuse };
            texture::texture_wrapping _wrapping{ texture::texture_wrapping ::repeat };
            texture::texture_filtering _filtering{ texture::texture_filtering ::nearest };
        };
    } // namespace assetsystem
} // namespace mix
