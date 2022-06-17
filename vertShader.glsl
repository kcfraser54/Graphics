#version 430 
layout (location=0) in vec3 position;
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf;
out vec4 varyingColor;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);
mat4 buildScale(float x, float y, float z);

void main(void) { 
	float i = gl_InstanceID + tf;
	float a = sin(50.0 * i/100.0) * 75.5;
	float b = sin(75.5 * i/200.0) * 50.0;
	float c = sin(100.0 * i/300.0) * 100.5;

	mat4 localRotX = buildRotateX(i);
	mat4 localRotY = buildRotateY(i);
	mat4 localRotZ = buildRotateZ(i);
	mat4 localTrans = buildTranslate(a, b, c);
	mat4 localScale = buildScale(1.2, 1.2, 1.2);

	mat4 newM_matrix = m_matrix * localScale * localTrans * localRotX * localRotY * localRotZ;
	mat4 mv_matrix = v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
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



















