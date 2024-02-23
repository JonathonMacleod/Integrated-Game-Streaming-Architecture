#include <spdlog/spdlog.h>


#include "graphics/Graphics.h"

#include "graphics/Cameras.h"
#include "graphics/Shaders.h"
#include "graphics/Models.h"
#include "graphics/Entities.h"

//
// Internal Functionality
//

static int GetHexValue(const char value) {
	const int unboundedIntValue = (value >= 'A') ? (value - 'A' + 10) : (value - '0');
	return (unboundedIntValue > 16 ? 0 : unboundedIntValue);
}

static int GetTwoDigitHexValue(const std::string& twoDigitHex) {
	const int firstDigitValue = GetHexValue(twoDigitHex.at(0));
	const int secondDigitValue = GetHexValue(twoDigitHex.at(1));

	const int value = (firstDigitValue << 4) | (secondDigitValue);
	return value;
}

static glm::vec3 GetColour(const std::string& hex) {
	int intR = GetTwoDigitHexValue(hex.substr(0, 2));
	int intG = GetTwoDigitHexValue(hex.substr(2, 2));
	int intB = GetTwoDigitHexValue(hex.substr(4, 2));

	float floatR = (intR / 255.0f);
	float floatG = (intG / 255.0f);
	float floatB = (intB / 255.0f);

	return glm::vec3(floatR, floatG, floatB);
}



// Input Functionality

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS) {
		if(key == GLFW_KEY_W)
			
	}
}



//
// Main Function
//

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

	// Set OpenGL renderings states to prevent items from rendering when behind other items
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Attempt to create a test shader program
	GSA::Graphics::ShaderProgram* shader = GSA::Graphics::ShaderProgram::GetShaderProgram("test", "res/shaders/shader_test");
	if(shader == NULL)
		spdlog::error("Failed to create test shader program");
	else
		spdlog::trace("Successfully created test shader program");

	// Create models
	GSA::Graphics::Model* cubeModel = GSA::Graphics::Model::CreateColouredCube(GetColour("031D44"), GetColour("04395E"),
																			   GetColour("70A288"), GetColour("DAB785"),
																			   GetColour("D5896F"), GetColour("FFA0FD"));
	GSA::Graphics::Model* surfaceModel = GSA::Graphics::Model::CreateColouredCube(GetColour("304D6D"), GetColour("304D6D"), 
																				  GetColour("A7CCED"), GetColour("A7CCED"), 
																				  GetColour("63ADF2"), GetColour("63ADF2"));

	// Create entities
	GSA::Graphics::Entity cubeEntity(cubeModel);
	cubeEntity.SetScale(0.5f, 0.5f, 0.5f);
	GSA::Graphics::Entity leftWallEntity(surfaceModel);
	leftWallEntity.SetTranslation(2.125f, 0.0f, 0.0f)->SetScale(0.25f, 3.5f, 3.0f);
	GSA::Graphics::Entity rightWallEntity(surfaceModel);
	rightWallEntity.SetTranslation(-2.125f, 0.0f, 0.0f)->SetScale(0.25f, 3.5f, 3.0f);
	GSA::Graphics::Entity backWallEntity(surfaceModel);
	backWallEntity.SetTranslation(0.0f, 0.0f, 1.625f)->SetScale(4.0f, 3.5f, 0.25f);
	GSA::Graphics::Entity bottomFloorEntity(surfaceModel);
	bottomFloorEntity.SetTranslation(0.0f, -1.625f, 0.0f)->SetScale(4.0f, 0.25f, 3.0f);

	// Create camera
	GSA::Graphics::Camera camera(640.0f, 480.f, 60.0f, 0.01f, 100.0f);
	camera.SetPosition(0.0f, 0.0f, -4.5f);

	// Keep a window alive until closed and draw some contents to the screen
	while(!glfwWindowShouldClose(window)) {
		// Clear the graphics context of any previously drawn graphics
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Rotate(0.0003f, 0.00000f);

		// Draw the triangle!
		if(shader != NULL) {
			shader->Bind();
			shader->SetUniformMatrix4(0, camera.GetViewMatrix());
			shader->SetUniformMatrix4(2, camera.GetPerspectiveMatrix());

			// Draw the cube
			cubeEntity.Draw(shader);

			// Draw the surfaces
			leftWallEntity.Draw(shader);
			rightWallEntity.Draw(shader);
			backWallEntity.Draw(shader);
			bottomFloorEntity.Draw(shader);

			shader->Unbind();
		}

		// Check for inputs and show any graphics drawn
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Destroy GLFW window
	glfwDestroyWindow(window);

	// Cleanup
	delete cubeModel;
	delete surfaceModel;
	delete shader;

	// Terminate GLFW
	glfwTerminate();

	return 0;
}
