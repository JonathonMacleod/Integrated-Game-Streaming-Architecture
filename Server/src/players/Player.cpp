#include "Player.h"

namespace GSA::Players {

	void Player::SetPosition(float x, float y, float z) { m_Camera.SetPosition(x, y, z); }
	void Player::Move(float x, float y, float z) { m_Camera.Move(x, y, z); }

	void Player::SetRotation(float pitchRadians, float yawRadians) { m_Camera.SetRotation(pitchRadians, yawRadians); }
	void Player::Rotate(float pitchDeltaRadians, float yawDeltaRadians) { m_Camera.Rotate(pitchDeltaRadians, yawDeltaRadians); }

	const Graphics::Camera& Player::GetCamera() { return m_Camera; }

}