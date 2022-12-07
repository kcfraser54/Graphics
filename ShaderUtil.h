#pragma once

#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <GL\glew.h>
#include <GLFW/glfw3.h>
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

private:
	void checkCompileErrors(GLuint shader, std::string type);
};

#endif

