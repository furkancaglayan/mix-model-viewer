#pragma once
#include <memory>
#include <string>
#include "mixAsset_item.h"
#include "../../math/vec.h"

namespace mix
{
    class shader
    {
        shader () = delete;
        ~shader () = delete;

        public:

        enum class shader_type : unsigned int
        {
            vertex = GL_VERTEX_SHADER,
            fragment = GL_FRAGMENT_SHADER,
            invalid
        };
        static shader_type get_shader_type (const std::string& ext)
        {
            if (ext == "vert")
            {
                return shader_type::vertex;
            }
            else if (ext == "frag")
            {
                return shader_type::fragment;
            }

            return shader_type::invalid;
        }
    };

    namespace assetsystem
    {
        class mixShader : public mix::assetsystem::mixAsset_item
        {
            public:

            mixShader (const mix::platform::mixAsset_path& path, const std::string& source, mix::shader::shader_type type);
            mixShader (const mix::platform::mixAsset_path& path);
            ~mixShader ();

            void compile (const std::string& source, mix::shader::shader_type type);

         
           
            inline const mix::shader::shader_type get_shader_type () const
            {
                return _type;
            }

            inline const unsigned get_shader_id () const
            {
                return shader_id;
            }

         

            //void set2fv (const std::string& s, vec2 v);
            //void set3fv (const std::string& s, vec3 v);
            //void set4fv (const std::string& s, vec4 v);

            private:

            const mix::shader::shader_type _type;
            unsigned shader_id{};
            bool is_compiled;
        };
    } // namespace assetsystem
} // namespace mix
