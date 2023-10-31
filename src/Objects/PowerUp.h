#pragma once
#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct PowerUp
	{
		Vector2 position;
		float size{20};
		bool isActive;
	};

	void PowerUpStart(PowerUp& powerUp, Vector2 position);
	void PowerUpReset(PowerUp& powerUp);

	void PowerUpDraw(PowerUp& powerUp);
	void PowerUpDrawCollider(PowerUp& powerUp);

	void PowerUpDestroy(PowerUp& powerUp);

}