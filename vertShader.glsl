#version 430 
layout (location=0) in vec3 vertPos;
layout (location=1) in vec3 vertNormal;

// eye-space vertex normal
out vec3 varyingNormal;

// vector point to the light
out vec3 varyingLightDir;

// vertex position in eye space 
out vec3 varyingVertPos;

struct positionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform vec4 globalAmbient;
uniform positionalLight light;
uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

// for transforming normals
uniform mat4 norm_matrix;

void main(void)
{   
	// output vertex position, light direction, and normal to the rasterizer or interpolation 
	varyingVertPos = (mv_matrix * vec4(vertPos, 1.0)).xyz;
	varyingLightDir = light.position - varyingVertPos;
	varyingNormal = (norm_matrix * vec4(vertNormal, 1.0)).xyz;

	gl_Position= proj_matrix * mv_matrix * vec4(vertPos, 1.0);
}



















