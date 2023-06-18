#include "Cameras.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GSA::Graphics {

	Camera::Camera(int outputWidth, int outputHeight, float fovDegrees, float nearDistance, float farDistance) {
		SetOutputSize(outputWidth, outputHeight);
		SetFOV(fovDegrees);
		SetNearAndFarDistances(nearDistance, farDistance);
	}

	void Camera::SetPosition(float x, float y, float z) {
		m_CameraPosition.x = x;
		m_CameraPosition.y = y;
		m_CameraPosition.z = z;
	}
	void Camera::Move(float x, float y, float z) { SetPosition(m_CameraPosition.x + x, m_CameraPosition.y + y, m_CameraPosition.z + z); }

	void Camera::MoveForwards(float delta) { m_CameraPosition += (delta * m_CameraFront); }
	void Camera::MoveBackwards(float delta) { m_CameraPosition -= (delta * m_CameraFront); }
	void Camera::MoveLeft(float delta) { m_CameraPosition -= (delta * glm::normalize(glm::cross(m_CameraFront, m_CameraUp))); }
	void Camera::MoveRight(float delta) { m_CameraPosition += (delta * glm::normalize(glm::cross(m_CameraFront, m_CameraUp))); }

	void Camera::SetRotation(float yawRadians, float pitchRadians) {
		m_CameraYawRadians = yawRadians;
		m_CameraPitchRadians = pitchRadians;

		if(m_CameraPitchRadians > glm::radians<float>(89))
			m_CameraPitchRadians = glm::radians<float>(89);
		if(m_CameraPitchRadians < glm::radians<float>(-89))
			m_CameraPitchRadians = glm::radians<float>(-89);

		glm::vec3 front = {
			cos(m_CameraYawRadians) * cos(m_CameraPitchRadians),
			sin(m_CameraPitchRadians),
			sin(m_CameraYawRadians) * cos(m_CameraPitchRadians)
		};
		m_CameraFront = glm::normalize(front);
	}
	void Camera::Rotate(float yawDeltaRadians, float pitchDeltaRadians) { SetRotation(m_CameraYawRadians + yawDeltaRadians, m_CameraPitchRadians + pitchDeltaRadians); }

	void Camera::SetOutputSize(int outputWidth, int outputHeight) {
		m_OutputWidth = outputWidth;
		m_OutputHeight = outputHeight;

		const float fovRadians = glm::radians<float>(m_CameraFOVDegrees);
		const float aspectRatio = ((float) m_OutputWidth) / ((float) m_OutputHeight);

		m_PerspectiveMatrix = glm::perspective(fovRadians, aspectRatio, m_CameraNearPlane, m_CameraFarPlane);
	}
	void Camera::SetFOV(float fovDegrees) {
		m_CameraFOVDegrees = fovDegrees;

		const float fovRadians = glm::radians<float>(m_CameraFOVDegrees);
		const float aspectRatio = ((float) m_OutputWidth) / ((float) m_OutputHeight);

		m_PerspectiveMatrix = glm::perspective(fovRadians, aspectRatio, m_CameraNearPlane, m_CameraFarPlane);
	}
	void Camera::SetNearAndFarDistances(float nearDistance, float farDistance) {
		m_CameraNearPlane = nearDistance;
		m_CameraFarPlane = farDistance;

		const float fovRadians = glm::radians<float>(m_CameraFOVDegrees);
		const float aspectRatio = ((float) m_OutputWidth) / ((float) m_OutputHeight);

		m_PerspectiveMatrix = glm::perspective(fovRadians, aspectRatio, m_CameraNearPlane, m_CameraFarPlane);
	}

	const glm::vec3& Camera::GetPosition() const { return m_CameraPosition; }
	float Camera::GetYaw() const { return m_CameraYawRadians; }
	float Camera::GetPitch() const { return m_CameraPitchRadians; }
	float Camera::GetFOVDegrees() const { return m_CameraFOVDegrees; }
	float Camera::GetNearPlane() const { return m_CameraNearPlane; }
	float Camera::GetFarPlane() const { return m_CameraFarPlane; }
	int Camera::GetOutputWidth() const { return m_OutputWidth; }
	int Camera::GetOutputHeight() const { return m_OutputHeight; }

	glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp); }
	const glm::mat4& Camera::GetPerspectiveMatrix() const { return m_PerspectiveMatrix; }

}