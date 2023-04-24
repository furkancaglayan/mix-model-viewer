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
            diffuse,
            normal,
            specular,
            height
        };

        enum class texture_wrapping : int
        {
            repeat = GL_REPEAT,
            mirrored_repeat = GL_MIRRORED_REPEAT,
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

        texture () = delete;
        ~texture () = delete;
    };

    namespace assetsystem
    {
        class mixTexture : public mix::assetsystem::mixAsset_item
        {
            public:

            inline const mix::texture::texture_type get_texture_type () const
            {
                return _type;
            }

            void set_wrapping (texture::texture_wrapping wrapping);

            void set_filtering (texture::texture_filtering filtering);

            private:

            unsigned int _id;
            const texture::texture_type _type;
            const texture::texture_wrapping _wrapping{ texture::texture_wrapping ::repeat };
            const texture::texture_filtering _filtering{ texture::texture_filtering ::nearest };
        };
    } // namespace assetsystem
} // namespace mix
