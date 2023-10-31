#pragma once
#include "Objects/PowerUp.h"

namespace asteroids
{
	void SpawnPowerUp(Vector2 position, PowerUp powerUps[], int powerUpsQty);

	void DrawPowerUps(PowerUp powerUps[], int powerUpsQty);
}