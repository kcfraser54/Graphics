#version 430 
in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec3 varyingHalfVector;
out vec4 fragColor;

// uniforms match those in the vertex shader,
// but aren't used directly in this fragment shader

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
	// normalize the light, normal, and view vectors
	vec3 L = normalize(varyingLightDir);
	vec3 N = normalize(varyingNormal);
	vec3 V = normalize(-varyingVertPos);
	vec3 H = normalize(varyingHalfVector);

	float cosTheta = dot(L, N);
	float cosPhi = dot(H, N);

	// compute ADS contributions (per pixel), and combine to build output color
	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta, 0.0);

	// the multiplication by 3.0 at the end is a "tweak" to improve the specular hightlight 
	vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(cosPhi,0.0), material.shininess * 3.0);

	fragColor = vec4((ambient + diffuse + specular), 1.0);

}