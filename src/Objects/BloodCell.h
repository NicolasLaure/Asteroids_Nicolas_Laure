#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct BloodCell
	{
		bool isActive;

		Vector2 position;
		Vector2 dir;
		float speed{100};

		float size{ 20 };
	};

	void BloodCellsStart(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellsUpdate(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellsDraw(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellsColliderDraw(BloodCell bloodCells[], int bloodCellsQty);
}
