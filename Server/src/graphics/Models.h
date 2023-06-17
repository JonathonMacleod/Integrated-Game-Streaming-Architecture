#ifndef GSA__MODELS__H
	#define GSA__MODELS__H

	#include <vector>

	#include "Graphics.h"

	namespace GSA::Graphics {
		
		class Model {
			public:
				Model();
				~Model();

				void Set3DPositionsBuffer(const float* positionsArray, GLsizeiptr arraySize);
				void SetIndexBuffer(const unsigned int* indexBufferArray, GLsizeiptr arraySize);
				void SetColoursBuffer(const float* coloursArray, GLsizeiptr arraySize);

				void Draw() const;

			private:
				GLuint m_VertexArrayObjectId = 0;
				GLuint m_IndexBufferObject = 0;
				bool m_HasIndexBufferObject = false;
				std::vector<GLuint> m_VertexBufferObjectIds;

				GLsizei m_NumberOfVertices = 0;
				GLsizei m_NumberOfIndices = 0;
		};

	}

#endif