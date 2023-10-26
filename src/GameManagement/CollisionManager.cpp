#include "CollisionManager.h"

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

						if (distanceBetweenCircles <= gd.player.bullets[i].size + gd.bloodCells[j].size)
						{
							gd.player.bullets[i].isActive = false;
							gd.bloodCells[j].isActive = false;
						}
					}
				}
				for (int j = 0; j < gd.VIRUSES_QTY; j++)
				{
					if (gd.viruses[j].isActive)
					{
						float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.viruses[j].position.x) + gd.viruses[j].currentSize / 2 - bulletPosition.x, 2) + pow(static_cast<double>(gd.viruses[j].position.y) - bulletPosition.y, 2)));

						if (distanceBetweenCircles <= gd.viruses[j].currentSize + gd.player.bullets[i].size)
						{
							gd.player.bullets[i].isActive = false;

							if (gd.viruses[j].phase == 1)
							{
								gd.viruses[j].phase = 2;
								gd.viruses[j].dir = { gd.player.bullets[i].direction.y * -1, gd.player.bullets[i].direction.x };
								gd.viruses[j].currentSize = gd.viruses[j].smallSize;
								for (int k = 0; k < gd.VIRUSES_QTY; k++)
								{
									if (!gd.viruses[k].isActive)
									{
										gd.viruses[k].isActive = true;
										gd.viruses[k].position = gd.viruses[j].position;
										gd.viruses[k].dir = { gd.player.bullets[i].direction.y, gd.player.bullets[i].direction.x * -1 };
										gd.viruses[k].currentSize = gd.viruses[j].currentSize;
										gd.viruses[k].phase = 2;
										break;
									}
								}
							}
							else if (gd.viruses[j].phase == 2)
							{
								gd.viruses[j].phase = 3;
								gd.viruses[j].currentSize = gd.viruses[j].miniSize;
								for (int k = 0; k < gd.VIRUSES_QTY; k++)
								{
									if (!gd.viruses[k].isActive)
									{
										gd.viruses[k].isActive = true;
										gd.viruses[k].position = gd.viruses[j].position;
										gd.viruses[k].dir = { gd.player.bullets[i].direction.y, gd.player.bullets[i].direction.x * -1 };
										gd.viruses[k].currentSize = gd.viruses[j].currentSize;
										gd.viruses[k].phase = 3;
										break;
									}
								}
							}
							else
								gd.viruses[j].isActive = false;

							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < gd.VIRUSES_QTY; i++)
		{
			if (gd.viruses[i].isActive)
			{

				float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.viruses[i].position.x) + gd.viruses[i].currentSize / 2 - gd.player.position.x, 2) + pow(static_cast<double>(gd.viruses[i].position.y) - gd.player.position.y, 2)));

				if (distanceBetweenCircles <= gd.player.colliderRadius + gd.viruses[i].currentSize)
				{
					gd.viruses[i].isActive = false;
					TakeDamage(gd.player, gd.isGameOver);
				}
			}
		}
	}
}