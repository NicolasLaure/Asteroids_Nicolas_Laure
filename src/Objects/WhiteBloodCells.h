#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct WhiteCell
	{
		bool isActive;

		Vector2 position;
		Vector2 dir;
		float speed{ 100 };
		float baseSpeed{ 150 };
		float angle{ 0 };
		float rotation{ 20 };

		int phase{ 1 };
		float currentSize{ 20 };
		float normalSize{ 20 };
		float smallSize{ 12.5f };
		float miniSize{ 7.5f };
		float speedMultiplier{ 1.3f };
		float secondPhaseSpeedMultiplier{ 1.6f };

		bool canTrackPlayer{ true };
		int minDistanceToTrack{ 125 };
	};

	void WhiteCellStart(WhiteCell& whiteCell);
	void WhiteCellsSpawner(WhiteCell whiteCells[], int whiteCellsQty);
	void WhiteCellUpdate(WhiteCell& whiteCell, Vector2 playerPosition);
	void WhiteCellDraw(WhiteCell& whiteCell);
	void WhiteCellColliderDraw(WhiteCell& whiteCell);
	void WhiteCellShrink(WhiteCell& whiteCell, Vector2 position);
	void WhiteCellDestroy(WhiteCell& whiteCell);
}