#ifndef GSA__ENTITIES__H
	#define GSA__ENTITIES__H

	#include <glm/vec3.hpp>
	#include <glm/mat4x4.hpp>

	#include "Models.h"
	#include "Shaders.h"

	namespace GSA::Graphics {
	
		class Entity {
			public:
				Entity(const Model* model);

				Entity* Translate(float x, float y, float z);
				Entity* Scale(float x, float y, float z);

				Entity* SetTranslation(float x, float y, float z);
				Entity* SetScale(float x, float y, float z);

				void Draw(const ShaderProgram* shader) const;

				const Model* GetModel() const;
				glm::mat4 GetModelMatrix() const;

			private:
				const Model* m_Model;

				glm::vec3 m_ScenePosition = glm::vec3(0.0f, 0.0f, 0.0f);
				glm::vec3 m_ModelScale = glm::vec3(1.0f, 1.0f, 1.0f);
		};

	}

#endif