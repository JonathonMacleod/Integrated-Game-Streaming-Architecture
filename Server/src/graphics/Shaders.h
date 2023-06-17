#ifndef GSA__SHADER__H
	#define GSA__SHADER__H

	#include <string>
	#include <vector>
	
	#include <glm/mat4x4.hpp>

	#include "Graphics.h"

	namespace GSA::Graphics {
		
		class ShaderProgram {
			public:
				static ShaderProgram* GetShaderProgram(const std::string& shaderName, const std::string& shaderDirectory);

			public:
				~ShaderProgram();

				void Bind() const;
				void Unbind() const;

				void SetUniformMatrix4(GLint uniformLocation, const glm::mat4& matrix) const;

			private:
				ShaderProgram(GLuint programId);

			private:
				GLuint m_ShaderProgramId = 0;
		};
		
	}

#endif