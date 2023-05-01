#include "mixShader_program.h"


mix::assetsystem::mixShader_program::mixShader_program (const mix::platform::mixAsset_path& path,
                                                        const shader& vertex_shader,
                                                        const shader& fragment_shader)
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

void mix::assetsystem::mixShader_program::set_1f (int loc, float f) const
{
    glUniform1f (loc, f);
}

void mix::assetsystem::mixShader_program::set_vec3 (int loc, vec3 vec) const
{
    glUniform3f (loc, vec.x, vec.y, vec.z);
}

void mix::assetsystem::mixShader_program::set_vec4 (int loc, vec4 vec) const
{
    glUniform4f (loc, vec.x, vec.y, vec.z, vec.w);
}

void mix::assetsystem::mixShader_program::set_mat3 (int loc, mat3 mat) const
{
    glUniformMatrix3fv (loc, 1, false, &mat[0][0]);
}

void mix::assetsystem::mixShader_program::set_mat4 (int loc, mat4 mat) const
{
    glUniformMatrix4fv (loc, 1, false, &mat[0][0]);
}

void mix::assetsystem::mixShader_program::set_1f (const std::string& s, float f) const
{
    glUniform1f (get_uniform_location (s), f);
}

void mix::assetsystem::mixShader_program::set_vec3 (const std::string& s, vec3 vec) const
{
    glUniform3f (get_uniform_location (s), vec.x, vec.y, vec.z);
}

void mix::assetsystem::mixShader_program::set_vec4 (const std::string& s, vec4 vec) const
{
    glUniform4f (get_uniform_location (s), vec.x, vec.y, vec.z, vec.w);
}

void mix::assetsystem::mixShader_program::set_mat3 (const std::string& s, mat3 mat) const
{
    glUniformMatrix3fv (get_uniform_location (s), 1, false, &mat[0][0]);
}

void mix::assetsystem::mixShader_program::set_mat4 (const std::string& s, mat4 mat) const
{
    glUniformMatrix4fv (get_uniform_location (s), 1, false, &mat[0][0]);
}


unsigned mix::assetsystem::mixShader_program::get_program_id () const
{
    return program_id;
}
