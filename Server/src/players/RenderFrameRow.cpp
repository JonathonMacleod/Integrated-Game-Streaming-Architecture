#include "PlayerFrameRow.h"

namespace GSA::Players {

	PlayerFrameRow::PlayerFrameRow(int maximumWidth) { m_MaximumRowWidth = maximumWidth; }

	bool PlayerFrameRow::AddPlayer(std::shared_ptr<Player> player) { 
		if(m_NumberOfPlayers >= GSA__MAX_PLAYERS_PER_FRAME_ROW) 
			return false;

		int playerWidth = player->GetCamera().GetOutputWidth();
		int playerHeight = player->GetCamera().GetOutputHeight();

		if((m_CurrentRowWidth + playerWidth) >= m_MaximumRowWidth)
			return false;

		if(playerHeight > m_CurrentRowHeight)
			if((m_MaximumRowHeight != -1) && (playerHeight > m_MaximumRowHeight))
				return false;

		m_Players[m_NumberOfPlayers] = player;
		m_AreRenderBoundariesDirty = true;
	}
	bool PlayerFrameRow::RemovePlayer(std::shared_ptr<Player> player) { }

	void PlayerFrameRow::LockRowHeight() { m_MaximumRowHeight = m_CurrentRowHeight; }
	void PlayerFrameRow::UnlockRowHeight() { m_MaximumRowHeight = -1; }

	int PlayerFrameRow::GetCurrentWidth() const { return m_CurrentRowWidth; }
	int PlayerFrameRow::GetCurrentHeight() const { return m_CurrentRowHeight; }
	int PlayerFrameRow::GetCurrentNumberOfPlayers() const { return m_NumberOfPlayers; }

	const glm::mat2x2* PlayerFrameRow::GetPlayerRenderBoundaries() {
		if(m_AreRenderBoundariesDirty) {
			int workingWidth = 0;
			for(int i = 0; i < m_NumberOfPlayers; i++) {
				const std::shared_ptr<Player> workingPlayer = m_Players[i];
				const int workingPlayerWidth = workingPlayer->GetCamera().GetOutputWidth();
				const int workingPlayerHeight = workingPlayer->GetCamera().GetOutputHeight();

				m_PlayerRenderBoundaries[i] = {
					workingWidth, 0, workingPlayerWidth, workingPlayerHeight
				};
				
				workingWidth += workingPlayerWidth;
			}

			m_AreRenderBoundariesDirty = false;
		}

		return m_PlayerRenderBoundaries;
	}

}