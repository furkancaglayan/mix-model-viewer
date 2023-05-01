#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coords;
layout(location = 3) in vec3 tangents;
layout(location = 4) in vec2 bitangents;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_tex_coords;

void main()
{
    gl_Position = _projection * _view * _model * vec4(pos, 1.0);

    frag_pos = vec3(_model * vec4(pos, 1.0));
    frag_normal = mat3(transpose(inverse(_model))) * normal;
    frag_tex_coords = tex_coords;
}
