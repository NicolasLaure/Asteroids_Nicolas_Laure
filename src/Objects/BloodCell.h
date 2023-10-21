#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct BloodCell
	{
		bool isActive;

	};


	void BloodCellsStart(BloodCell bloodCells[]);
	void BloodCellsUpdate(BloodCell bloodCells[]);
	void BloodCellsDraw(BloodCell bloodCells[]);
	void BloodCellsColliderDraw(BloodCell bloodCells[]);
}
