#include "Shaders.h"

#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <filesystem>

//
// Internal Functionality
//

static bool ReadShaderFileSource(const std::string& shaderFilepath, GLchar*& fileSource, GLsizei& fileSourceLength) {
	// Open an input filestream to the shader source file
	std::ifstream fileStream(shaderFilepath.c_str());
	if(!fileStream.is_open()) {
		spdlog::error("Failed to open shader source file '{}'", shaderFilepath.c_str());
		return false;
	}

	// Read the source file line-by-line until no more lines are found
	std::string currentSourceFileLine;
	std::stringstream sourceFileStringStream;
	while(std::getline(fileStream, currentSourceFileLine)) {
		// It doesn't matter whether you add an extraneous newline character to the end of a shader source file 
		sourceFileStringStream << currentSourceFileLine << "\n";
	}

	// Assemble the source file string from the string stream and copy the characters of the file into heap memory
	std::string sourceFileString = sourceFileStringStream.str();
	GLchar* newFileSourceBuffer = new GLchar[sourceFileString.length()];
	std::memcpy(newFileSourceBuffer, sourceFileString.c_str(), sourceFileString.length());

	// Return the source contents and length of the source file
	fileSource = newFileSourceBuffer;
	fileSourceLength = (GLsizei) sourceFileString.length();
	return true;
}

static GLuint CompileShader(const std::string& shaderName, const std::string& shaderTypeName, const std::string& shaderFilepath, GLenum shaderType) {
	// Read the source file for the shader
	GLchar* fileSource = NULL;
	GLsizei fileSourceLength = 0;
	if(!ReadShaderFileSource(shaderFilepath, fileSource, fileSourceLength)) {
		spdlog::error("Failed to read {} {} source file", shaderName, shaderTypeName);
		delete[] fileSource;
		return 0;
	}

	// Generate an ID for this shader
	GLuint shaderId = glCreateShader(shaderType);

	// Pass OpenGL the shader source code
	GLchar* sources[] = { fileSource };
	GLsizei sourceLengths[] = { fileSourceLength };
	glShaderSource(shaderId, 1, sources, sourceLengths);

	// Compile the code
	glCompileShader(shaderId);

	// Retrieve log information about the shaders
	GLint shaderLogLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &shaderLogLength);
	std::vector<GLchar> shaderLog;
	if(shaderLogLength > 0) {
		shaderLog.resize(shaderLogLength);
		glGetShaderInfoLog(shaderId, GL_INFO_LOG_LENGTH, nullptr, shaderLog.data());
	}

	// Check for compilation errors
	GLint compilationStatus = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);
	if(compilationStatus != GL_TRUE) {
		glDeleteShader(shaderId);
		spdlog::error("Failed to compile {} {} shader source. Error log: {}", shaderName, shaderTypeName, (char*) shaderLog.data());
		return 0;
	}

	// Free the shader source file and return the shader ID
	delete[] fileSource;
	return shaderId;
}



namespace GSA::Graphics {

	//
	// ShaderProgram Class Implementations
	//

	ShaderProgram* ShaderProgram::GetShaderProgram(const std::string& shaderName, const std::string& shaderDirectory) {
		// Create a shader program
		GLuint programId = glCreateProgram();

		// Compile vertex shader and attach it to the shader program
		GLuint vertexShaderId = CompileShader(shaderName, "vertex", shaderDirectory + "/vertex.vert", GL_VERTEX_SHADER);
		if(vertexShaderId == 0) {
			spdlog::error("Failed to create {} shader (had an error compiling the vertex shader)", shaderName);
			glDeleteProgram(programId);
			return NULL;
		}
		glAttachShader(programId, vertexShaderId);
		
		// Compile fragment shader and attach it to the shader program
		GLuint fragmentShaderId = CompileShader(shaderName, "fragment", shaderDirectory + "/fragment.frag", GL_FRAGMENT_SHADER);
		if(fragmentShaderId == 0) {
			spdlog::error("Failed to create {} shader (had an error compiling the fragment shader)", shaderName);
			glDeleteShader(vertexShaderId);
			glDeleteProgram(programId);
			return NULL;
		}
		glAttachShader(programId, fragmentShaderId);

		// Link the shader program and mark the shaders for deletion once the shader program is deleted
		glLinkProgram(programId);
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		// Retrieve log information about the shader program after linking the shaders
		GLint programLogLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &programLogLength);
		std::vector<GLchar> shaderProgramLog;
		if(programLogLength > 0) {
			shaderProgramLog.resize(programLogLength);
			glGetProgramInfoLog(programId, GL_INFO_LOG_LENGTH, nullptr, shaderProgramLog.data());
		}

		// Check for shader program linking errors
		GLint linkingStatus = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &linkingStatus);
		if(linkingStatus != GL_TRUE) {
			spdlog::error("Failed to create {} shader, had an error during linking: {}", shaderName, shaderProgramLog.data());
			glDeleteProgram(programId);
			return NULL;
		}

		// Return a new shader program that uses the program ID
		ShaderProgram* newShader = new ShaderProgram(programId);
		return newShader;
	}

	ShaderProgram::ShaderProgram(GLuint programId) { m_ShaderProgramId = programId; }
	ShaderProgram::~ShaderProgram() { glDeleteProgram(m_ShaderProgramId); }

	void ShaderProgram::Bind() const { glUseProgram(m_ShaderProgramId); }
	void ShaderProgram::Unbind() const { glUseProgram(0); }

	void ShaderProgram::SetUniformMatrix4(GLint uniformLocation, const glm::mat4& matrix) const {
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}