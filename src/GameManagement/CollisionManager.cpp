#include "CollisionManager.h"

#include "Objects/Patient.h"

namespace asteroids
{
	void CheckCollisions(GameData& gd)
	{
		for (int i = 0; i < gd.player.BULLETS_QTY; i++)
		{
			if (gd.player.bullets[i].isActive)
			{
				Vector2 bulletPosition = { gd.player.bullets[i].position.x + gd.player.bullets[i].size / 2, gd.player.bullets[i].position.y + gd.player.bullets[i].size / 2 };
				for (int j = 0; j < gd.BLOOD_CELLS_QTY; j++)
				{
					if (gd.bloodCells[j].isActive)
					{

						float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.bloodCells[j].position.x) - bulletPosition.x, 2) + pow(static_cast<double>(gd.bloodCells[j].position.y) - bulletPosition.y, 2)));

						if (distanceBetweenCircles <= gd.player.bullets[i].size + gd.bloodCells[j].currentSize)
						{
							gd.player.bullets[i].isActive = false;
							PatientTakeDamage(gd.patient, gd.hasWon);
							
							if (gd.bloodCells[j].phase == 1)
							{
								gd.bloodCells[j].phase = 2;
								gd.bloodCells[j].dir = { gd.player.bullets[i].direction.y * -1, gd.player.bullets[i].direction.x };
								gd.bloodCells[j].currentSize = gd.bloodCells[j].smallSize;
								for (int k = 0; k < gd.WHITECELLS_QTY; k++)
								{
									if (!gd.bloodCells[k].isActive)
									{
										gd.bloodCells[k].isActive = true;
										gd.bloodCells[k].position = gd.bloodCells[j].position;
										gd.bloodCells[k].dir = { gd.player.bullets[i].direction.y, gd.player.bullets[i].direction.x * -1 };
										gd.bloodCells[k].currentSize = gd.bloodCells[j].currentSize;
										gd.bloodCells[k].phase = 2;
										break;
									}
								}
							}
							else if (gd.bloodCells[j].phase == 2)
							{
								gd.bloodCells[j].phase = 3;
								gd.bloodCells[j].currentSize = gd.bloodCells[j].miniSize;
								for (int k = 0; k < gd.WHITECELLS_QTY; k++)
								{
									if (!gd.bloodCells[k].isActive)
									{
										gd.bloodCells[k].isActive = true;
										gd.bloodCells[k].position = gd.bloodCells[j].position;
										gd.bloodCells[k].dir = { gd.player.bullets[i].direction.y, gd.player.bullets[i].direction.x * -1 };
										gd.bloodCells[k].currentSize = gd.bloodCells[j].currentSize;
										gd.bloodCells[k].phase = 3;
										break;
									}
								}
							}
							else
								BloodCellDestroy(gd.bloodCells[j]);
						}
					}
				}
				for (int j = 0; j < gd.WHITECELLS_QTY; j++)
				{
					if (gd.whiteCells[j].isActive)
					{
						float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.whiteCells[j].position.x) + gd.whiteCells[j].currentSize / 2 - bulletPosition.x, 2) + pow(static_cast<double>(gd.whiteCells[j].position.y) - bulletPosition.y, 2)));

						if (distanceBetweenCircles <= gd.whiteCells[j].currentSize + gd.player.bullets[i].size)
						{
							gd.player.bullets[i].isActive = false;

							if (gd.whiteCells[j].phase == 1)
							{
								gd.whiteCells[j].phase = 2;
								gd.whiteCells[j].dir = { gd.player.bullets[i].direction.y * -1, gd.player.bullets[i].direction.x };
								gd.whiteCells[j].currentSize = gd.whiteCells[j].smallSize;
								for (int k = 0; k < gd.WHITECELLS_QTY; k++)
								{
									if (!gd.whiteCells[k].isActive)
									{
										gd.whiteCells[k].isActive = true;
										gd.whiteCells[k].position = gd.whiteCells[j].position;
										gd.whiteCells[k].dir = { gd.player.bullets[i].direction.y, gd.player.bullets[i].direction.x * -1 };
										gd.whiteCells[k].currentSize = gd.whiteCells[j].currentSize;
										gd.whiteCells[k].phase = 2;
										break;
									}
								}
							}
							else if (gd.whiteCells[j].phase == 2)
							{
								gd.whiteCells[j].phase = 3;
								gd.whiteCells[j].currentSize = gd.whiteCells[j].miniSize;
								for (int k = 0; k < gd.WHITECELLS_QTY; k++)
								{
									if (!gd.whiteCells[k].isActive)
									{
										gd.whiteCells[k].isActive = true;
										gd.whiteCells[k].position = gd.whiteCells[j].position;
										gd.whiteCells[k].dir = { gd.player.bullets[i].direction.y, gd.player.bullets[i].direction.x * -1 };
										gd.whiteCells[k].currentSize = gd.whiteCells[j].currentSize;
										gd.whiteCells[k].phase = 3;
										break;
									}
								}
							}
							else
								gd.whiteCells[j].isActive = false;

							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < gd.WHITECELLS_QTY; i++)
		{
			if (gd.whiteCells[i].isActive)
			{

				float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.whiteCells[i].position.x) + gd.whiteCells[i].currentSize / 2 - gd.player.position.x, 2) + pow(static_cast<double>(gd.whiteCells[i].position.y) - gd.player.position.y, 2)));

				if (distanceBetweenCircles <= gd.player.colliderRadius + gd.whiteCells[i].currentSize)
				{
					gd.whiteCells[i].isActive = false;
					TakeDamage(gd.player, gd.isGameOver);
				}
			}
		}
	}
}