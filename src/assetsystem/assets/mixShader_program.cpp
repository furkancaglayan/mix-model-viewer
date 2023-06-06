#include "mixShader_program.h"


mix::assetsystem::mixShader_program::mixShader_program (const mix::platform::mixAsset_path& path, shader* vertex_shader, shader* fragment_shader)
: mix::assetsystem::mixAsset_item (path)
{
    compile (vertex_shader, fragment_shader);
}


mix::assetsystem::mixShader_program::~mixShader_program ()
{
    glDeleteProgram (program_id);
}

const unsigned mix::assetsystem::mixShader_program::get_uniform_location (const std::string& s) const
{
    return glGetUniformLocation (program_id, s.c_str ());
}

const unsigned mix::assetsystem::mixShader_program::get_uniform_location (const char* s) const
{
    return glGetUniformLocation (program_id, s);
}

void mix::assetsystem::mixShader_program::compile (shader* vertex_shader, shader* fragment_shader)
{
    program_id = glCreateProgram ();
    glAttachShader (program_id, vertex_shader->get_shader_id ());
    glAttachShader (program_id, fragment_shader->get_shader_id ());
    glLinkProgram (program_id);
}

void mix::assetsystem::mixShader_program::use () const
{
    glUseProgram (program_id);
}

void mix::assetsystem::mixShader_program::set_1f( const std::string& s, float f)
{
    glUniform1f (get_uniform_location (s), f);
}

void mix::assetsystem::mixShader_program::set_1i (const std::string& s, int i)
{
    glUniform1i (get_uniform_location (s), i);
}

void mix::assetsystem::mixShader_program ::set_vec3 (const std::string& s, vec3 vec)
{
    glUniform3f (get_uniform_location (s), vec.x, vec.y, vec.z);
}

void mix::assetsystem::mixShader_program::set_vec4 (const std::string& s, vec4 vec)
{
    glUniform4f (get_uniform_location (s), vec.x, vec.y, vec.z, vec.w);
}

void mix::assetsystem::mixShader_program::set_mat3 (const std::string& s, mat3 mat)
{
    glUniformMatrix3fv (get_uniform_location (s), 1, false, &mat[0][0]);
}

void mix::assetsystem::mixShader_program::set_mat4 (const std::string& s, mat4 mat)
{
    glUniformMatrix4fv (get_uniform_location (s), 1, false, &mat[0][0]);
}


unsigned mix::assetsystem::mixShader_program::get_program_id () const
{
    return program_id;
}
