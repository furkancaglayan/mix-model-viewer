#include "mixShader_program.h"


mix::assetsystem::mixShader_program::mixShader_program (const mix::platform::mixAsset_path& path,
                                                        const mix::assetsystem::mixShader& vertex_shader,
                                                        const mix::assetsystem::mixShader& fragment_shader)
: mix::assetsystem::mixAsset_item (path)
{
    compile (vertex_shader, fragment_shader);
}

mix::assetsystem::mixShader_program::~mixShader_program ()
{
}

void mix::assetsystem::mixShader_program::compile (const mix::assetsystem::mixShader& vertex_shader,
                                                   const mix::assetsystem::mixShader& fragment_shader)
{
    program_id = glCreateProgram ();
    glAttachShader (program_id, vertex_shader.get_shader_id ());
    glAttachShader (program_id, fragment_shader.get_shader_id ());
    glLinkProgram (program_id);
}

void mix::assetsystem::mixShader_program::use () const
{
    glUseProgram (program_id);
}

unsigned mix::assetsystem::mixShader_program::get_program_id () const
{
    return program_id;
}
