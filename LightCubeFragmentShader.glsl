#version 430 core
out vec4 FragColor;


struct Light {
    vec3 Position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;


void main()
{
    FragColor = vec4(1.0); 
}