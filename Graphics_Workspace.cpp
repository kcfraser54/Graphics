#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <fstream>
#include <cmath>
#include <stack>
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "util.h"
#include "Sphere.h"
using namespace std;

#define numVAOs 1
#define numVBOs 3

float cameraX, cameraY, cameraZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
GLuint mapTexture;
util utility;
stack<glm::mat4> mvStack;
Sphere mySphere(48);

// allocate variables used in display() function, so that they won't need to be allocated 
// during rendering 

GLuint mvLoc, projLoc, vLoc, tfLoc, mLoc;
int width, height, tf, timeFactor;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;

// 36 vertices, 12 triangles, makes a 2x2x2 cube placed at the origin 
void setupVertices(void) {

	std::vector<int> ind = mySphere.getIndices();
	std::vector<glm::vec3> vert = mySphere.getVertices();
	std::vector<glm::vec2> tex = mySphere.getTexCoords();
	std::vector<glm::vec3> norm = mySphere.getNormals();

	// vertex positions
	std::vector<float> pvalues;

	// texture coordinates
	std::vector<float> tvalues;

	// normal vectors
	std::vector<float> nvalues;

	int numIndices = mySphere.getNumIndices();

	for (int i = 0; i < numIndices; i++) {
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);

		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);

		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(3, vbo);

	// put the vertices into buffer #0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);

}


void init(GLFWwindow* window) {
	renderingProgram = utility.createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 10.0f;

	setupVertices();

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.01f, 1000.0f);

	// Load in the texture image 
	mapTexture = utility.loadTexture("map.jpg");
}

void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight) {

	// new width and height provided by the callback 
	aspect = (float)newWidth / (float)newHeight;

	// sets screen region associated with framebuffer
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void display(GLFWwindow* window, double currentTime) {

	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	// uniform variables 
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	// push view matrix onto the stack 
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mvStack.push(vMat);

	//-------------------------------- Object ---------------------------//
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // object position;
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f)); // object rotation

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mapTexture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices()); // draw the sun
	mvStack.pop();
	mvStack.pop();
}


/*
* Main includes a very simple rendering loop that calls out display() function repeatedly
* It also calls glfwSwapBuffers(), which paints the screen, and glfwPollEvents(), which handles
* other window related events (such as key being pressed)
*/
int main() {

	// glfw library initialized
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// window hints set options for the created window 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// last two parameters allow for full screen mode and window sharing 
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Sphere", NULL, NULL);

	// Creating a glfw window does not automatically make the associated OpenGL context current
	glfwMakeContextCurrent(window);

	// glew library initialized 
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}

	// vertical synchronization enabled
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(window, window_reshape_callback);
	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());

		// vertical synchronization enabled 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}