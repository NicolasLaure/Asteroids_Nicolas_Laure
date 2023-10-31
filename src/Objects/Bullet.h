#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct Bullet
	{
		Vector2 position;
		Vector2 direction;
		const float speed = 500;

		bool isActive;

		float angle{};
		const float size = 10;
	};

	void BulletsStart(Bullet bullets[], int bulletsQty);
	void BulletUpdate(Bullet& bullet);
	void BulletDraw(Bullet& bullet);
	void BulletColliderDraw(Bullet& bullet);
}