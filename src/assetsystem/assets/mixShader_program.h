#pragma once
#include "mixShader.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

            void compile (const mix::assetsystem::mixShader& vertex_shader, const mix::assetsystem::mixShader& fragment_shader);
            void use () const;
            void set_vec3 (int loc, glm::vec3 vec) const;
            void set_vec4 (int loc, glm::vec4 vec) const;
            unsigned get_program_id () const;

            private:

            unsigned program_id{};
        };
    } // namespace assetsystem
} // namespace mix
