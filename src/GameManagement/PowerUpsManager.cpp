#include "GameManagement/PowerUpsManager.h"

namespace asteroids
{
	void SpawnPowerUp(Vector2 position, PowerUp powerUps[], int powerUpsQty)
	{
		for (int i = 0; i < powerUpsQty; i++)
		{
			if (!powerUps[i].isActive)
			{
				PowerUpStart(powerUps[i], position);
				break;
			}
		}
	}
	void PowerUpsReset(PowerUp powerUps[], int powerUpsQty)
	{
		for (int i = 0; i < powerUpsQty; i++)
		{
			PowerUpReset(powerUps[i]);
		}
	}

	void DrawPowerUps(PowerUp powerUps[], int powerUpsQty)
	{
		for (int i = 0; i < powerUpsQty; i++)
		{
			PowerUpDraw(powerUps[i]);
#ifdef _DEBUG
			PowerUpDrawCollider(powerUps[i]);
#endif
		}
	}
}