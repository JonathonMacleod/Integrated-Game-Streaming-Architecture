#ifndef GSA__SHADER__H
	#define GSA__SHADER__H

	#include <string>
	#include <vector>
	
	#include "Graphics.h"

	namespace GSA::Graphics {
		
		class ShaderProgram {
			public:
				static ShaderProgram* GetShaderProgram(const std::string& shaderName, const std::string& shaderDirectory);

			private:
				ShaderProgram(GLuint programId);

			public:
				~ShaderProgram();

				void Bind() const;
				void Unbind() const;

			private:
				GLuint m_ShaderProgramId = 0;
		};
		
	}

#endif