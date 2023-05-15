#pragma once
#include "../../math/mat.h"
#include "../../math/vec.h"
#include "mixShader.h"
#include <string>

namespace mix
{
    namespace assetsystem
    {
        class mixShader_program : public mix::assetsystem::mixAsset_item
        {
            using shader = mix::assetsystem::mixShader;

            public:

            mixShader_program (const mix::platform::mixAsset_path& path, const shader& vertex_shader, const shader& fragment_shader);


            mixShader_program () = delete;
            ~mixShader_program ();

            const unsigned get_uniform_location (const std::string& s) const;
            const unsigned get_uniform_location (const char* s) const;

            void compile (const mix::assetsystem::mixShader& vertex_shader, const mix::assetsystem::mixShader& fragment_shader);
            void use () const;

          
            void set_1f (const std::string& s, float f);
            void set_vec3 (const std::string& s, vec3 vec);
            void set_vec4 (const std::string& s, vec4 vec);
            void set_mat3 (const std::string& s, mat3 mat);
            void set_mat4 (const std::string& s, mat4 mat);

            unsigned get_program_id () const;

            private:

            unsigned program_id{};
        };
    } // namespace assetsystem
} // namespace mix
