#pragma once
#include "GameManagement/AsteroidsHandler.h"

namespace asteroids
{
	void AsteroidsStart(GameData& gd)
	{
		for (int i = 0; i < gd.BLOOD_CELLS_QTY; i++)
		{
			BloodCellStart(gd.bloodCells[i]);
		}
		for (int i = 0; i < gd.WHITECELLS_QTY; i++)
		{
			WhiteCellStart(gd.whiteCells[i]);
		}
	}

	void AsteroidsUpdate(GameData& gd)
	{
		BloodCellsSpawner(gd.bloodCells, gd.BLOOD_CELLS_QTY);
		WhiteCellsSpawner(gd.whiteCells, gd.WHITECELLS_QTY);
		for (int i = 0; i < gd.BLOOD_CELLS_QTY; i++)
		{
			BloodCellUpdate(gd.bloodCells[i]);
		}
		for (int i = 0; i < gd.WHITECELLS_QTY; i++)
		{
			WhiteCellUpdate(gd.whiteCells[i]);
		}
	}
	void AsteroidsDraw(GameData& gd)
	{
		for (int i = 0; i < gd.BLOOD_CELLS_QTY; i++)
		{
			BloodCellDraw(gd.bloodCells[i]);
		}
		for (int i = 0; i < gd.WHITECELLS_QTY; i++)
		{
			WhiteCellDraw(gd.whiteCells[i]);
		}
	}
	void AsteroidsDebugDraw(GameData& gd) 
	{
		for (int i = 0; i < gd.BLOOD_CELLS_QTY; i++)
		{
			BloodCellColliderDraw(gd.bloodCells[i]);
		}
		for (int i = 0; i < gd.WHITECELLS_QTY; i++)
		{
			WhiteCellColliderDraw(gd.whiteCells[i]);
		}
	}
}