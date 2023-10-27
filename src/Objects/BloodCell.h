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

		int phase{ 1 };
		float currentSize{ 20 };
		float normalSize{ 20 };
		float smallSize{ 12.5f };
		float miniSize{ 7.5f };
	};

	void BloodCellsStart(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellsUpdate(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellsDraw(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellsColliderDraw(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellDestroy(BloodCell& bloodCell);
}
