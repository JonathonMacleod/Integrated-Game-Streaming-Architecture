#include "spdlog/spdlog.h"
#include "graphics/Graphics.h"

#include "graphics/Shaders.h"

int main(int argc, char* args[]) {
	spdlog::set_level(spdlog::level::trace);

	// Initialise GLFW
	if(!glfwInit()) {
		spdlog::error("Failed to initialise GLFW");
		return -1;
	}

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialise GLEW
	GLenum err = glewInit();
	if(GLEW_OK != err) {
		spdlog::error("GLEW error occurred: {}", (char*) glewGetErrorString(err));
		return -1;
	}
	spdlog::info("Using GLEW {}", (char*) glewGetString(GLEW_VERSION));

	// Attempt to create a test shader program
	GSA::Graphics::ShaderProgram* shaders = GSA::Graphics::ShaderProgram::GetShaderProgram("test", "res/shaders/shader_test");
	if(shaders == NULL) 
		spdlog::error("Failed to create test shader program");
	else
		spdlog::trace("Successfully created test shader program");

	while(true) {
		// Just keep the window open
		glfwPollEvents();
		glfwSwapBuffers(window);

		if(glfwWindowShouldClose(window)) {
			break;
		}
	}

	// Destroy GLFW window
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}
