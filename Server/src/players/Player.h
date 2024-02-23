#ifndef GSA__MODELS__H
	#define GSA__MODELS__H

	#include "../graphics/Cameras.h"

	namespace GSA::Players {
		
		class Player {
			public:
				void SetPosition(float x, float y, float z);
				void Move(float x, float y, float z);

				void SetRotation(float pitchRadians, float yawRadians);
				void Rotate(float pitchDeltaRadians, float yawDeltaRadians);

				const Graphics::Camera& GetCamera();

			private:
				GSA::Graphics::Camera m_Camera = GSA::Graphics::Camera(640.0f, 480.f, 60.0f, 0.01f, 100.0f);
		};

	}

#endif