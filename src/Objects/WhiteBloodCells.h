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

		int phase{ 1 };
		float currentSize{ 20 };
		float normalSize{ 20 };
		float smallSize{ 12.5f };
		float miniSize{ 7.5f };
	};

	void WhiteCellsStart(WhiteCell whiteCells[], int whiteCellsQty);
	void WhiteCellsUpdate(WhiteCell whiteCells[], int whiteCellsQty);
	void WhiteCellsDraw(WhiteCell whiteCells[], int whiteCellsQty);
	void WhiteCellsColliderDraw(WhiteCell whiteCells[], int whiteCellsQty);
}