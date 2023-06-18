#ifndef GSA__CAMERAS__H
	#define GSA__CAMERAS__H

	#include <glm/glm.hpp>

	namespace GSA::Graphics {

		class Camera {
			public:
				Camera(int outputWidth = 100, int outputHeight = 100, float fovDegrees = 60.0f, float nearDistance = 0.01f, float farDistance = 100.0f);

				void SetPosition(float x, float y, float z);
				void Move(float x, float y, float z);

				void MoveForwards(float delta);
				void MoveBackwards(float delta);
				void MoveLeft(float delta);
				void MoveRight(float delta);

				void SetRotation(float pitchRadians, float yawRadians);
				void Rotate(float pitchDeltaRadians, float yawDeltaRadians);

				void SetOutputSize(int outputWidth = 100, int outputHeight = 100);
				void SetFOV(float fovDegrees = 60.0f);
				void SetNearAndFarDistances(float nearDistance = 0.1f, float farDistance = 100.0f);

				const glm::vec3& GetPosition() const;
				float GetYaw() const;
				float GetPitch() const;
				float GetFOVDegrees() const;
				float GetNearPlane() const;
				float GetFarPlane() const;
				int GetOutputWidth() const;
				int GetOutputHeight() const;

				glm::mat4 GetViewMatrix() const;
				const glm::mat4& GetPerspectiveMatrix() const;

			private:
				glm::mat4 m_PerspectiveMatrix;

				int m_OutputWidth = 100;
				int m_OutputHeight = 100;
				float m_CameraFOVDegrees = 60.0f;
				float m_CameraNearPlane = 0.1f;
				float m_CameraFarPlane = 100.0f;

				float m_CameraPitchRadians = 0.0f;
				float m_CameraYawRadians = -90.0f;
				glm::vec3 m_CameraUp = glm::vec3(0, 1, 0);
				glm::vec3 m_CameraPosition = glm::vec3(0, 0, 0);
				glm::vec3 m_CameraFront = glm::vec3(0, 0, 1);
		};

	}

#endif