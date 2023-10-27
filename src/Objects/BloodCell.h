#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct BloodCell
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

	void BloodCellsSpawner(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellStart(BloodCell& bloodCell);
	void BloodCellUpdate(BloodCell& bloodCell);
	void BloodCellDraw(BloodCell& bloodCell);
	void BloodCellColliderDraw(BloodCell& bloodCell);
	void BloodCellDestroy(BloodCell& bloodCell);
}
