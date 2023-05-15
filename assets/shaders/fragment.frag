#version 330 core
#define MAX_LIGHTS 128

in vec3 frag_pos;
in vec3 frag_normal;
//in vec3 frag_tex_coords;

uniform vec4 _color;
uniform float _shininess;
uniform vec3 _view_pos;

out vec4 FragColor;

uniform int num_lights;
uniform struct Light {
    vec3 position;
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float intensity;
    float attenuation;
} lights[MAX_LIGHTS];

vec3 calculate_light(Light light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(frag_normal);
    vec3 viewDir = normalize(_view_pos - frag_pos);

    vec3 result;
     for(int i = 0; i < num_lights; i++)
        result += calculate_light(lights[i], norm, viewDir); 

  FragColor = vec4(result, 1.0) * _color;
}

vec3 calculate_light(Light light, vec3 normal, vec3 viewDir)
{
    vec3 ambient = light.ambient * light.diffuse;

    vec3 lightDir = normalize(light.position - frag_pos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 diffuse = diff * light.diffuse;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _shininess);
    vec3 specular = light.specular *spec;

    vec3 result = (ambient + diffuse + specular);
    return result * light.intensity;
}  
