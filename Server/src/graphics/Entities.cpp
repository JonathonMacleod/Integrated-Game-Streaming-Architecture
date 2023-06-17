#include "Entities.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GSA::Graphics {

	Entity::Entity(const Model* model) : m_Model(model) { }

	Entity* Entity::Translate(float x, float y, float z) { return SetTranslation(m_ScenePosition.x + x, m_ScenePosition.y + y, m_ScenePosition.z + z); }
	Entity* Entity::Scale(float x, float y, float z) { return SetScale(m_ModelScale.x + x, m_ModelScale.y + y, m_ModelScale.z + z); }

	Entity* Entity::SetTranslation(float x, float y, float z) {
		m_ScenePosition.x = x;
		m_ScenePosition.y = y;
		m_ScenePosition.z = z;
		return this;
	}
	Entity* Entity::SetScale(float x, float y, float z) {
		m_ModelScale.x = x;
		m_ModelScale.y = y;
		m_ModelScale.z = z;
		return this;
	}

	void Entity::Draw(const ShaderProgram* shader) const {
		if(shader != NULL)
			shader->SetUniformMatrix4(1, GetModelMatrix());

		if(m_Model != NULL)
			m_Model->Draw();
	}

	const Model* Entity::GetModel() const { return m_Model; }

	glm::mat4 Entity::GetModelMatrix() const {
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_ScenePosition);
		modelMatrix = glm::scale(modelMatrix, m_ModelScale);
		return modelMatrix;
	}

}