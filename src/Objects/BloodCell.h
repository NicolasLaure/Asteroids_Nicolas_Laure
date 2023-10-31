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
	};

	void BloodCellStart(BloodCell& bloodCell);
	void BloodCellsSpawner(BloodCell bloodCells[], int bloodCellsQty);
	void BloodCellUpdate(BloodCell& bloodCell);
	void BloodCellDraw(BloodCell& bloodCell);
	void BloodCellColliderDraw(BloodCell& bloodCell);
	void BloodCellDivision(BloodCell& bloodCell, Vector2 position, Vector2 dir);
	void BloodCellDestroy(BloodCell& bloodCell);
}
