#pragma once

#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderUtil
{

public:

	// the program id
	GLuint ID;

	// constructor reads and builds the shader
	ShaderUtil(const char* vertexPath, const char* fragmentPath);

	// use/activate the shader
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4f(const std::string& name, float r, float g, float b, float a) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;




private:
	void checkCompileErrors(GLuint shader, std::string type);
};

#endif

