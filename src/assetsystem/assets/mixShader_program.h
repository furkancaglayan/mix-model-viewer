#pragma once
#include "mixShader.h"
#include <string>

namespace mix
{
    namespace assetsystem
    {
        class mixShader_program : public mix::assetsystem::mixAsset_item
        {
            public:

            mixShader_program (const mix::platform::mixAsset_path& path,
                               const mix::assetsystem::mixShader& vertex_shader,
                               const mix::assetsystem::mixShader& fragment_shader);
            mixShader_program () = delete;
            ~mixShader_program ();

            void compile (const mix::assetsystem::mixShader& vertex_shader, const mix::assetsystem::mixShader& fragment_shader);
            void use () const;
            unsigned get_program_id () const;

            private:

            unsigned program_id{};
        };
    } // namespace assetsystem
} // namespace mix
