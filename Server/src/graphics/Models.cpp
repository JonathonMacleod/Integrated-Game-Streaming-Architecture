#include "Models.h"

//
// Internal Functionality
//
static GLuint getAttachedVBO(GLuint vaoId, const void* byteArray, GLsizeiptr byteArraySize, GLuint attribIndex, GLint attribSize, GLenum dataType, GLenum bufferUsage) {
	glBindVertexArray(vaoId);

	// Generate a buffer with the vertex data and bind it
	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// Put data into the buffer
	glBufferData(GL_ARRAY_BUFFER, byteArraySize, byteArray, bufferUsage);

	// Bind the buffer object to the chosen attribute in the vertex array object
	glVertexAttribPointer(attribIndex, attribSize, dataType, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribIndex);

	// Cleanup (unbind the vertex array and buffer)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vertexBuffer;
}



namespace GSA::Graphics {

	//
	// Model Class Implementations
	//

	Model* Model::CreateColouredCube(const glm::vec3& faceColour) { 
		return CreateColouredCube(faceColour, faceColour, faceColour, faceColour, faceColour, faceColour); 
	}
	Model* Model::CreateColouredCube(const glm::vec3& topFaceColour, const glm::vec3& bottomFaceColour, const glm::vec3& sideFaceColour) { 
		return CreateColouredCube(topFaceColour, bottomFaceColour, sideFaceColour, sideFaceColour, sideFaceColour, sideFaceColour); 
	}
	Model* Model::CreateColouredCube(const glm::vec3& topFaceColour, const glm::vec3& bottomFaceColour, const glm::vec3& leftFaceColour, const glm::vec3& rightFaceColour,
									 const glm::vec3& backFaceColour, const glm::vec3& frontFaceColour) {
		// Define cube model values
		constexpr float cubeVertices[] = {
			// Front face
			-0.5, -0.5,  0.5, 
			 0.5, -0.5,  0.5, 
			 0.5,  0.5,  0.5, 
			-0.5,  0.5,  0.5,
			// Back face
			-0.5, -0.5, -0.5, 
			-0.5,  0.5, -0.5, 
			 0.5,  0.5, -0.5, 
			 0.5, -0.5, -0.5,
			// Top face
			-0.5,  0.5, -0.5, 
			-0.5,  0.5,  0.5, 
			 0.5,  0.5,  0.5, 
			 0.5,  0.5, -0.5,
			// Bottom face
			-0.5, -0.5, -0.5, 
			 0.5, -0.5, -0.5, 
			 0.5, -0.5,  0.5, 
			-0.5, -0.5,  0.5,
			// Right face
			 0.5, -0.5, -0.5, 
			 0.5,  0.5, -0.5, 
			 0.5,  0.5,  0.5, 
			 0.5, -0.5,  0.5,
			// Left face
			-0.5, -0.5, -0.5, 
			-0.5, -0.5,  0.5, 
			-0.5,  0.5,  0.5, 
			-0.5,  0.5, -0.5
		};
		constexpr unsigned int cubeIndices[] = {
			// Front face
			 0,  1,  2,
			 0,  2,  3,
			// Back face
			 4,  5,  6,
			 4,  6,  7,
			// Top face
			 8,  9, 10,
			 8, 10, 11,   
			// Bottom face
			12, 13, 14,
			12, 14, 15,
			// Right face
			16, 17, 18,
			16, 18, 19,
			// Left face
			20, 21, 22,
			20, 22, 23
		};
		const float cubeColours[] = {
			// Front face
			frontFaceColour.r, frontFaceColour.g, frontFaceColour.b,
			frontFaceColour.r, frontFaceColour.g, frontFaceColour.b,
			frontFaceColour.r, frontFaceColour.g, frontFaceColour.b,
			frontFaceColour.r, frontFaceColour.g, frontFaceColour.b,
			// Back face
			backFaceColour.r, backFaceColour.g, backFaceColour.b,
			backFaceColour.r, backFaceColour.g, backFaceColour.b,
			backFaceColour.r, backFaceColour.g, backFaceColour.b,
			backFaceColour.r, backFaceColour.g, backFaceColour.b,
			// Top face
			topFaceColour.r, topFaceColour.g, topFaceColour.b,
			topFaceColour.r, topFaceColour.g, topFaceColour.b,
			topFaceColour.r, topFaceColour.g, topFaceColour.b,
			topFaceColour.r, topFaceColour.g, topFaceColour.b,
			// Bottom face
			bottomFaceColour.r, bottomFaceColour.g, bottomFaceColour.b,
			bottomFaceColour.r, bottomFaceColour.g, bottomFaceColour.b,
			bottomFaceColour.r, bottomFaceColour.g, bottomFaceColour.b,
			bottomFaceColour.r, bottomFaceColour.g, bottomFaceColour.b,
			// Right face
			rightFaceColour.r, rightFaceColour.g, rightFaceColour.b,
			rightFaceColour.r, rightFaceColour.g, rightFaceColour.b,
			rightFaceColour.r, rightFaceColour.g, rightFaceColour.b,
			rightFaceColour.r, rightFaceColour.g, rightFaceColour.b,
			// Left face
			leftFaceColour.r, leftFaceColour.g, leftFaceColour.b,
			leftFaceColour.r, leftFaceColour.g, leftFaceColour.b,
			leftFaceColour.r, leftFaceColour.g, leftFaceColour.b,
			leftFaceColour.r, leftFaceColour.g, leftFaceColour.b
		};

		// Construct cube model from model values
		GSA::Graphics::Model* cubeModel = new GSA::Graphics::Model();
		cubeModel->Set3DPositionsBuffer(cubeVertices, sizeof(cubeVertices));
		cubeModel->SetColoursBuffer(cubeColours, sizeof(cubeColours));
		cubeModel->SetIndexBuffer(cubeIndices, sizeof(cubeIndices));

		return cubeModel;
	}

	Model::Model() { glGenVertexArrays(1, &m_VertexArrayObjectId); }

	Model::~Model() { 
		// Delete all the attached vertex buffer objects
		glDeleteBuffers((GLsizei) m_VertexBufferObjectIds.size(), m_VertexBufferObjectIds.data());

		// Delete the vertex array object
		glDeleteVertexArrays(1, &m_VertexArrayObjectId);

		// Delete the index buffer object (if one was used)
		if(m_HasIndexBufferObject)
			glDeleteBuffers(1, &m_IndexBufferObject);
	}

	void Model::Set3DPositionsBuffer(const float* positionsArray, GLsizeiptr arraySizeInBytes) { 
		GLuint positionsBuffer = getAttachedVBO(m_VertexArrayObjectId, positionsArray, arraySizeInBytes, 0, 3, GL_FLOAT, GL_STATIC_DRAW);
		m_VertexBufferObjectIds.push_back(positionsBuffer);

		m_NumberOfVertices = ((GLsizei) arraySizeInBytes) / ((GLsizei) sizeof(unsigned int));
	}

	void Model::SetIndexBuffer(const unsigned int* indexBufferArray, GLsizeiptr arraySizeInBytes) { 
		// Bind the vertex array
		glBindVertexArray(m_VertexArrayObjectId);

		// Generate an index buffer and bind it
		glGenBuffers(1, &m_IndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);

		// Put data into the buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, arraySizeInBytes, indexBufferArray, GL_STATIC_DRAW);

		// Unbind the index buffer and the vertex array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Mark the model as using an index buffer when drawing, and record the number of indices
		m_HasIndexBufferObject = true;
		m_NumberOfIndices = ((GLsizei) arraySizeInBytes) / ((GLsizei) sizeof(unsigned int));
	}

	void Model::SetColoursBuffer(const float* coloursArray, GLsizeiptr arraySizeInBytes) {
		GLuint coloursBuffer = getAttachedVBO(m_VertexArrayObjectId, coloursArray, arraySizeInBytes, 1, 3, GL_FLOAT, GL_STATIC_DRAW);
		m_VertexBufferObjectIds.push_back(coloursBuffer);
	}

	void Model::Draw() const { 
		// Bind the vertex array
		glBindVertexArray(m_VertexArrayObjectId);

		if(m_HasIndexBufferObject) {
			// If an index buffer has been provided, bind the index buffer and then draw the elements provided
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
			glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, nullptr);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		} else {
			// If no index buffer was provided, draw using the bound vertex array only
			glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVertices);
		}

		// Unbind the vertex array
		glBindVertexArray(0);
	}

}
