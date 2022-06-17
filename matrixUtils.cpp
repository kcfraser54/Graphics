#include "matrixUtils.h"
#include <GL\glew.h>
#include "glm\glm.hpp"
#include <cmath>
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"


// builds and returns a translation matrix 
glm::mat4 matrixUtils::buildTranslate(float x, float y, float z) {
	glm::mat4 translate = glm::mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		x, y, z, 1.0);
	
	return translate;
}

// builds and returns matrix that performs a rotation around the x axis
glm::mat4 matrixUtils::buildRotateX(float rad) {
	glm::mat4 rotateX = glm::mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(rad), -sin(rad), 0.0,
		0.0, sin(rad), cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);

	return rotateX;
}

// builds and returns matrix that performs a rotation around the y axis
glm::mat4 matrixUtils::buildRotateY(float rad) {
	glm::mat4 rotateY = glm::mat4(cos(rad), 0.0, sin(rad), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(rad), 0.0, cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);

	return rotateY;

}

// builds and returns matrix that performs a rotation around the z axis
glm::mat4 matrixUtils::buildRotateZ(float rad) {
	glm::mat4 rotateZ = glm::mat4(cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return rotateZ;
}

// builds and returns a scale matrix
glm::mat4 matrixUtils::buildScale(float x, float y, float z) {
	glm::mat4 scale = glm::mat4(x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return scale;
}
