#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coords;
layout(location = 3) in vec3 tangents;
layout(location = 4) in vec3 bitangents;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

out VS_OUT {
    vec3 frag_pos;
    vec2 frag_tex_coords;
    mat3 _tbn;
} vs_out;


void main()
{
    gl_Position = _projection * _view * _model * vec4(pos, 1.0);

    vs_out.frag_tex_coords = tex_coords;
    vs_out.frag_pos = vec3(_model * vec4(pos, 1.0));   

    vec3 T = normalize(vec3(_model * vec4(tangents,   0.0)));
    vec3 B = normalize(vec3(_model * vec4(bitangents, 0.0)));
    vec3 N = normalize(vec3(_model * vec4(normal,    0.0)));
    vs_out._tbn = mat3(T, B, N);
}
