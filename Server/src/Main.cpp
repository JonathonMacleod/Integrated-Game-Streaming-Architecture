#include <iostream>

#include "spdlog/spdlog.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(int argc, char* args[]) {
	// Initialise GLFW
	if(!glfwInit()) {
		fprintf(stderr, "Failed to initialise GLFW\n");
		return EXIT_FAILURE;
	}

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialise GLEW
	GLenum err = glewInit();
	if(GLEW_OK != err) {
		fprintf(stderr, "GLEW error: %s\n", glewGetErrorString(err));
		return EXIT_FAILURE;
	}
	fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// Test spdlog
	spdlog::info("tpdlog test output");

	// Destroy GLFW window
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return EXIT_SUCCESS;
}
