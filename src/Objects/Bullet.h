#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct Bullet
	{
		float speed;
		Vector2 dir;

		bool isActive;

	};


	void BulletsStart(Bullet bullets[]);
	void BulletsUpdate(Bullet bullets[]);
	void BulletsDraw(Bullet bullets[]);
	void BulletsColliderDraw(Bullet bullets[]);
}