#pragma once
#include <memory>
#include <string>

namespace mix
{
    class shader
    {
        shader () = delete;
        ~shader () = delete;

        public:

        enum class shader_type : uint8_t
        {
            vertex,
            fragment,
            invalid
        };
        static shader_type get_shader_type (const std::string& ext)
        {
            if (ext == "vs")
            {
                return shader_type::vertex;
            }
            else if (ext == "fs")
            {
                return shader_type::fragment;
            }

            return shader_type::invalid;
        }
    };

    namespace assetsystem
    {
        class mixShader
        {
            public:

            inline const mix::shader::shader_type get_shader_type () const;
            inline const unsigned int get_shader_id ();
            const void load_from_text (const std::string& text);
            void compile ();

            private:

            const mix::shader::shader_type _type;
            unsigned int _id;
        };
    } // namespace assetsystem
} // namespace mix
