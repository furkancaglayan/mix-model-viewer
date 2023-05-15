#include "rendering_context.h"
#include "../assetsystem/assets/mixShader_program.h"

void mix::rendering::rendering_context::initialize () const
{
    /* glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

void mix::rendering::rendering_context::finalize () const
{
}


void mix::rendering::rendering_context::set_1f (int loc, float f)
{
    glUniform1f (loc, f);
}

void mix::rendering::rendering_context::set_1i (int loc, int i)
{
    glUniform1i (loc, i);
}

void mix::rendering::rendering_context::set_vec3 (int loc, vec3 vec)
{
    glUniform3f (loc, vec.x, vec.y, vec.z);
}

void mix::rendering::rendering_context::set_vec4 (int loc, vec4 vec)
{
    glUniform4f (loc, vec.x, vec.y, vec.z, vec.w);
}

void mix::rendering::rendering_context::set_mat3 (int loc, mat3 mat)
{
    glUniformMatrix3fv (loc, 1, false, &mat[0][0]);
}

void mix::rendering::rendering_context::set_mat4 (int loc, mat4 mat)
{
    glUniformMatrix4fv (loc, 1, false, &mat[0][0]);
}

void mix::rendering::rendering_context::set_1f (const std::string& s, float f)
{
    glUniform1f (glGetUniformLocation (_active_program, s.c_str ()), f);
}

void mix::rendering::rendering_context::set_1i (const std::string& s, int f)
{
    glUniform1i (glGetUniformLocation (_active_program, s.c_str ()), f);
}


void mix::rendering::rendering_context::set_vec3 (const std::string& s, vec3 vec)
{
    glUniform3f (glGetUniformLocation (_active_program, s.c_str ()), vec.x, vec.y, vec.z);
}

void mix::rendering::rendering_context::set_vec4 (const std::string& s, vec4 vec)
{
    glUniform4f (glGetUniformLocation (_active_program, s.c_str ()), vec.x, vec.y, vec.z, vec.w);
}

void mix::rendering::rendering_context::set_mat3 (const std::string& s, mat3 mat)
{
    glUniformMatrix3fv (glGetUniformLocation (_active_program, s.c_str ()), 1, false, &mat[0][0]);
}

void mix::rendering::rendering_context::set_mat4 (const std::string& s, mat4 mat)
{
    glUniformMatrix4fv (glGetUniformLocation (_active_program, s.c_str ()), 1, false, &mat[0][0]);
}
