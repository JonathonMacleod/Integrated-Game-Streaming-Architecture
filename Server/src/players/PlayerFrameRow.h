#ifndef GSA__PLAYERFRAMEROW__H
	#define GSA__PLAYERFRAMEROW__H

	#define GSA__MAX_PLAYERS_PER_FRAME_ROW 32

	#include "Player.h"

	#include <memory>
	#include <glm/glm.hpp>

	namespace GSA::Players {
		
		class PlayerFrameRow {
			public:
				PlayerFrameRow(int maximumWidth);

				bool AddPlayer(std::shared_ptr<Player> player);
				bool RemovePlayer(std::shared_ptr<Player> player);

				void LockRowHeight();
				void UnlockRowHeight();

				int GetCurrentWidth() const;
				int GetCurrentHeight() const;
				int GetCurrentNumberOfPlayers() const;

				const glm::mat2x2* GetPlayerRenderBoundaries();

			private:
				int m_NumberOfPlayers = 0;
				std::shared_ptr<Player> m_Players[GSA__MAX_PLAYERS_PER_FRAME_ROW];
				glm::mat2x2 m_PlayerRenderBoundaries[GSA__MAX_PLAYERS_PER_FRAME_ROW];

				// Store the current dimensions of the frame row
				int m_CurrentRowWidth = 0;
				int m_CurrentRowHeight = 0;

				// Store the maximum dimensions of the frame row
				int m_MaximumRowWidth;
				int m_MaximumRowHeight = -1;

				// Store whether the render boundaries for the players need to be recalculated
				bool m_AreRenderBoundariesDirty = true;
		};
	
	}

#endif