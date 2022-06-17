#pragma once

#include <GL\glew.h>
#include "glm\glm.hpp"
#include <cmath>
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"


class matrixUtils
{
public:

	// builds and returns a translation matrix 
	glm::mat4 buildTranslate(float x, float y, float z);

	// builds and returns matrix that performs a rotation around the x axis
	glm::mat4 buildRotateX(float rad);

	// builds and returns matrix that performs a rotation around the y axis
	glm::mat4 buildRotateY(float rad);

	// builds and returns matrix that performs a rotation around the z axis
	glm::mat4 buildRotateZ(float rad);

    // builds and returns a scale matrix
	glm::mat4 buildScale(float x, float y, float z);

private:
};

