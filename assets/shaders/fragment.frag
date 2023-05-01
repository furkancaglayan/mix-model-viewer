#version 330 core

in vec3 frag_pos;
in vec3 frag_normal;
//in vec3 frag_tex_coords;

uniform vec4 _color;
uniform vec3 _light;
uniform vec3 _light_pos;
uniform vec3 _view_pos;
uniform float _ambient;
uniform float _specular;
uniform float _shininess;

out vec4 FragColor;

void main()
{
   
    vec3 ambient = _ambient * _light;
    vec3 norm = normalize(frag_normal);

    vec3 lightDir = normalize(_light_pos - frag_pos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = diff * _light;

    vec3 viewDir = normalize(_view_pos - frag_pos);

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _shininess);
    vec3 specular = _specular * spec * _light;

    vec3 result = (ambient + diffuse + specular) * vec3(_color);

    FragColor = vec4(result, 1.0);
    //FragColor = vec4(1.0);
}
