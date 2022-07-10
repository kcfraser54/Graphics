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
#include "Torus.h"
using namespace std;

// declarations for building shaders and rendering programs, as before.
// declaration of one VAO, and two VBOs, and Torus as before 
// declaration and assignment of torus and camera location as before.
// Utils.cpp now has gold, silver, and bronze material accessors added

#define numVAOs 1
#define numVBOs 4

float cameraX, cameraY, cameraZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
GLuint mapTexture;
util utility;
Torus myTorus(0.5f, 0.2f, 48);


// allocate variables used in display() function, so that they won't need to be allocated 
// during rendering 
GLuint mvLoc, projLoc, vLoc, tfLoc, mLoc, nLoc;
int width, height, tf, timeFactor;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat, invTrMat;
float torLocX, torLocY, torLocZ;
// locations for shader uniform variables
GLuint globalAmbLoc, diffLoc, specLoc, posLoc, mAmbLoc, mDiffLoc, mShiLoc, ambLoc, mSpecLoc;

// light position as Vector3f, in both model and view space 
glm::vec3 currentLightPos, lightPosV;

// light position as float array
float lightPos[3];

// initial light location 
glm::vec3 initialLightLoc = glm::vec3(5.0f, 2.0f, 2.0f);

// white light properties
float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

// gold material properties
float* matAmb = utility.goldAmbient();
float* matDif = utility.goldDiffuse();
float* matSpe = utility.goldSpecular();
float matShi = utility.goldShininess();
 



// 36 vertices, 12 triangles, makes a 2x2x2 cube placed at the origin 
void setupVertices(void) {

	std::vector<int> ind = myTorus.getIndices();
	std::vector<glm::vec3> vert = myTorus.getVertices();
	std::vector<glm::vec2> tex = myTorus.getTexCoords();
	std::vector<glm::vec3> norm = myTorus.getNormals();

	// vertex positions
	std::vector<float> pvalues;

	// texture coordinates
	std::vector<float> tvalues;

	// normal vectors
	std::vector<float> nvalues;

	int numVertices = myTorus.getNumVertices();
	for (int i = 0; i < numVertices; i++) {
		pvalues.push_back(vert[i].x);
		pvalues.push_back(vert[i].y);
		pvalues.push_back(vert[i].z);

		tvalues.push_back(tex[i].s);
		tvalues.push_back(tex[i].t);

		nvalues.push_back(norm[i].x);
		nvalues.push_back(norm[i].y);
		nvalues.push_back(norm[i].z);
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(4, vbo);

	// put the vertices into buffer #0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]); // indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);

}


void init(GLFWwindow* window) {
	renderingProgram = utility.createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 10.0f;

	torLocX = 0.0f;
	torLocY = 0.0f;
	torLocZ = 4.2f;

	setupVertices();

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.01f, 1000.0f);

	// Load in the texture image 
	//mapTexture = utility.loadTexture("map.jpg");
}

void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight) {

	// new width and height provided by the callback 
	aspect = (float)newWidth / (float)newHeight;

	// sets screen region associated with framebuffer
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void installLights(glm::mat4 vMatrix) {
	// convert light's position to view space, and save it in a float array 
	lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
	lightPos[0] = lightPosV.x;
	lightPos[1] = lightPosV.y;
	lightPos[2] = lightPosV.z;

	// get the locations of the light and material fields
	globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");
	ambLoc = glGetUniformLocation(renderingProgram, "light.ambient");
	diffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
	specLoc = glGetUniformLocation(renderingProgram, "light.specular");
	posLoc = glGetUniformLocation(renderingProgram, "light.position");
	mAmbLoc = glGetUniformLocation(renderingProgram, "material.ambient");
    mDiffLoc = glGetUniformLocation(renderingProgram, "material.diffuse");
	mSpecLoc = glGetUniformLocation(renderingProgram, "material.specular");
	mShiLoc = glGetUniformLocation(renderingProgram, "material.shininess");

	// set the uniform light and materials in the shader
	glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
	glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
	glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
	glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
	glProgramUniform4fv(renderingProgram, posLoc, 1, lightPos);
	glProgramUniform4fv(renderingProgram, mAmbLoc, 1, matAmb);
	glProgramUniform4fv(renderingProgram, mDiffLoc, 1, matDif);
	glProgramUniform4fv(renderingProgram, mSpecLoc, 1, matSpe);
	glProgramUniform1f(renderingProgram, mShiLoc, matShi);
}

void display(GLFWwindow* window, double currentTime) {

	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	// uniform variables 
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");


	// push view matrix onto the stack 
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	// Build the model matrix based on the torus location 
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(torLocX, torLocY, torLocZ));
	
	// rotate the torus to make it easier to see
	mMat *= glm::rotate(mMat, myTorus.toRadians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// set up lights based on the current light's position
	currentLightPos = glm::vec3(initialLightLoc.x, initialLightLoc.y, initialLightLoc.z);
	installLights(vMat);

	// build the model-view matrix by concatenating matrices v and m, as before
	mvMat = vMat * mMat;

	// build the inverse transpose of the MV matrix, for transforming normal vectors
	invTrMat = glm::transpose(glm::inverse(mvMat));

	// put the MV, PROJ, and inverse-transpose (normal) matrixes into corresponding uniforms
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

	// bind the vertices buffer (VBO #0) to vertex attribute #0 in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(0);

	// bind the normals buffer (in VBO #2) to vertex attribute #1 in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
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
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Phong shading", NULL, NULL);

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