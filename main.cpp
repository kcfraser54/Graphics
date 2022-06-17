/*#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
using namespace std;

void init(GLFWwindow* window){}

void display(GLFWwindow* window, double currentTime) {

	// Specifies the color value to be applied when clearing the background 
	glClearColor(1.0, 0.0, 0.0, 1.0);

	// fill the color buffer with that color
	glClear(GL_COLOR_BUFFER_BIT);
}


/*
* Main includes a very simple rendering loop that calls out display() function repeatedly 
* It also calls glfwSwapBuffers(), which paints the screen, and glfwPollEvents(), which handles 
* other window related events (such as key being pressed)
*/

/*
int main() {

	// glfw library initialized
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// window hints set options for the created window 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// last two parameters allow for full screen mode and window sharing 
	GLFWwindow* window = glfwCreateWindow(600, 600, "Fuck Yeah", NULL, NULL);

	// Creating a glfw window does not automatically make the associated OpenGL context current
	glfwMakeContextCurrent(window);

	// glew library initialized 
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}

	// vertical synchronization enabled
	glfwSwapInterval(1);

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
*/