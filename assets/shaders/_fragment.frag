#version 330 core
#define MAX_LIGHTS 128
uniform vec3 _view_pos;
in VS_OUT {
    vec3 frag_pos;
    vec2 frag_tex_coords;
    mat3 _tbn;
} fs_in;

uniform vec4 _color;
uniform float _shininess;
uniform sampler2D texture0;
uniform sampler2D texture2;
uniform sampler2D texture4;

out vec4 FragColor;

uniform struct Light {
    vec3 position;
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float intensity;
    float attenuation;
};

uniform Light lights[MAX_LIGHTS];
vec3 calculate_light(Light light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 viewDir =normalize(_view_pos - fs_in.frag_pos);
    vec3 normal = normalize(fs_in._tbn * (texture(texture2, fs_in.frag_tex_coords).rgb * 2.0 - 1.0)); 

    vec3 result = vec3(0);
    for(int i = 0; i < MAX_LIGHTS; i++)
    {
        result += calculate_light(lights[i], normal, viewDir); 
    }

  FragColor = vec4(result, 1.0);
}

vec3 calculate_light(Light light, vec3 normal, vec3 viewDir)
{
    vec3 L =normalize(light.position -  fs_in.frag_pos);
    float kd = max(dot(L, normal), 0.0);

    vec3 color = vec3(texture(texture0, fs_in.frag_tex_coords));
    vec3 diffuse  = light.diffuse  * kd * color * light.intensity;

    vec3 ambient  = light.ambient  * color;

    vec3 reflectDir = reflect(-L, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _shininess);
    vec3 specular = light.specular * spec* light.intensity/* * vec3(texture(_specular, vec2(frag_tex_coords.x, frag_tex_coords.y)))*/;

    vec3 result = diffuse + ambient + specular;
    return result;
}
