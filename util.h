#pragma once

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
using namespace std;


class util
{
public:

	// Functions to create shader programs
	GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* gp, const char* fp);
	GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp);
	GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);
	GLuint createShaderProgram(const char* vp, const char* fp);

	// load textures
	GLuint loadTexture(const char* texImagePath);


	// materials

	// GOLD material - ambient, diffuse, specular, and shininess
	float* goldAmbient();
	float* goldDiffuse();
	float* goldSpecular();
	float goldShininess();

	// SILVER material - ambient, diffuse, specular, and shininess
	float* silverAmbient();
	float* silverDiffuse();
	float* silverSpecular();
	float silverShininess();

	// BRONZE materials - ambient, diffuse, specular, and shininess
	float* bronzeAmbient();
	float* bronzeDiffuse();
	float* bronzeSpecular();
	float bronzeShininess();

	//unsigned int loadCubeMap(vector<std::string> faces);

	void printMaxVertexAttributes();
	
private:
	// Error handling functions
	void printShaderLog(GLuint shader);
	void printProgramLog(int prog);
	bool checkOpenGLError();

	// read shader source code
	string readShaderSource(const char* filePath);

};

