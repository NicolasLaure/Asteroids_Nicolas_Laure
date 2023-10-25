#include "CollisionManager.h"

namespace asteroids
{
	void CheckCollisions(GameData& gd)
	{
		for (int i = 0; i < gd.player.BULLETS_QTY; i++)
		{
			Vector2 bulletPosition = { gd.player.bullets[i].position.x + gd.player.bullets[i].size / 2, gd.player.bullets[i].position.y + gd.player.bullets[i].size / 2 };
			for (int j = 0; j < gd.BLOOD_CELLS_QTY; j++)
			{
				if (gd.bloodCells[j].isActive)
				{

					float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.bloodCells[j].position.x - bulletPosition.x), 2) + pow(static_cast<double>(gd.bloodCells[j].position.y - bulletPosition.y), 2)));

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
					float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(gd.viruses[j].position.x + gd.viruses[j].size / 2 - bulletPosition.x), 2) + pow(static_cast<double>(gd.viruses[j].position.y - bulletPosition.y), 2)));

					if (distanceBetweenCircles <= gd.viruses[j].size + gd.player.bullets[i].size)
					{
						gd.player.bullets[i].isActive = false;
						gd.viruses[j].isActive = false;
					}
				}
			}
		}
	}
}