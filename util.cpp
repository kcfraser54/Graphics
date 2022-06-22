#include "util.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <SOIL2/SOIL2.h>
using namespace std;


// Functions to create shader programs
GLuint util::createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* gp, const char* fp) {
	GLuint dummy = -9999;
	return dummy;
}

GLuint util::createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp) {
	GLuint dummy = -9999;
	return dummy;
}

GLuint util::createShaderProgram(const char* vp, const char* gp, const char* fp) {
	GLuint dummy = -9999;
	return dummy;
}

GLuint util::createShaderProgram(const char* vp, const char* fp) {
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	string vertShaderStr = readShaderSource(vp);
	string fragShaderStr = readShaderSource(fp);

	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();


	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);

	// catch errors while compiling the vertex shader
	glCompileShader(vShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}

	// catch errors while compiling the fragment shader
	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fShader);
	}

	GLuint vfProgram = glCreateProgram();

	// catch errors while linking the program 
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}
	return vfProgram;
}

// Error handling functions
void util::printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}
void util::printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

bool util::checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

string util::readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint util::loadTexture(const char* texImagePath) {
	GLuint textureID;
	textureID = SOIL_load_OGL_texture(texImagePath,
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0) {
		cout << "could not find texture file " << texImagePath << endl;
	}

	// If mipmapping 
	glBindTexture(GL_TEXTURE_2D, textureID);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//float redColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, redColor);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

	// if also anisotropic filtering 
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
		GLfloat anisoSetting = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}

	return textureID;
}
