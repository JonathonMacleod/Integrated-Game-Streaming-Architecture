#include "spdlog/spdlog.h"
#include "graphics/Graphics.h"

#include "graphics/Shaders.h"
#include "graphics/Models.h"

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
	GSA::Graphics::ShaderProgram* shader = GSA::Graphics::ShaderProgram::GetShaderProgram("test", "res/shaders/shader_test");
	if(shader == NULL)
		spdlog::error("Failed to create test shader program");
	else
		spdlog::trace("Successfully created test shader program");

	// Create a triangle model
	constexpr float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	constexpr unsigned int triangleIndices[] = {
		0,  1,  2
	};
	constexpr float triangleColours[] = {
		0.8f, 0.2f, 0.0f,
		0.0f, 0.8f, 0.2f,
		0.2f, 0.0f, 0.8f
	};
	GSA::Graphics::Model* triangleModel = new GSA::Graphics::Model();
	triangleModel->Set3DPositionsBuffer(triangleVertices, sizeof(triangleVertices));
	triangleModel->SetColoursBuffer(triangleColours, sizeof(triangleColours));
	triangleModel->SetIndexBuffer(triangleIndices, sizeof(triangleIndices));

	while(!glfwWindowShouldClose(window)) {
		// Draw the triangle!
		if(shader != NULL) {
			shader->Bind();
			triangleModel->Draw();
			shader->Unbind();
		}

		// Check for inputs and show any graphics drawn
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Destroy GLFW window
	glfwDestroyWindow(window);

	// Cleanup
	delete triangleModel;
	delete shader;

	// Terminate GLFW
	glfwTerminate();

	return 0;
}
