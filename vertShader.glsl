#version 430 
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;

// texture coordinate output to rasterizer for interpolation
out vec2 tc; 

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

layout (binding=0) uniform sampler2D samp;  // not used in the vertex shader 

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);
mat4 buildScale(float x, float y, float z);

void main(void) { 
	gl_Position = buildRotateZ(45) * proj_matrix * mv_matrix * vec4(position, 1.0);
	tc = texCoord;
}

mat4 buildTranslate(float x, float y, float z) {
	mat4 translate = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		x, y, z, 1.0);
	
	return translate;
}

mat4 buildRotateX(float rad) {
	mat4 rotateX = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(rad), -sin(rad), 0.0,
		0.0, sin(rad), cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);

	return rotateX;
}

mat4 buildRotateY(float rad) {
	mat4 rotateY = mat4(cos(rad), 0.0, sin(rad), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(rad), 0.0, cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);

	return rotateY;
}

mat4 buildRotateZ(float rad) {
	mat4 rotateZ = mat4(cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return rotateZ;
}

mat4 buildScale(float x, float y, float z) {
	mat4 scale = mat4(x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return scale;
}



















