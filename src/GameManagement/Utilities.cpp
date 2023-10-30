#include "Utilities.h"

namespace asteroids
{
	Vector2 GetRandomPosition(float size)
	{
		int screenHeight = GetScreenHeight();
		int screenWidth = GetScreenWidth();
		Vector2 position;
		float posX;
		float posY;
		if (GetRandomValue(0, 1) == 0)
		{
			if (GetRandomValue(0, 1) == 0)
			{
				posX = 0 - size;
				posY = static_cast<float>(GetRandomValue(0, screenHeight));
			}
			else
			{
				posX = screenHeight + size;
				posY = static_cast<float>(GetRandomValue(0, screenHeight));
			}
		}
		else
		{
			if (GetRandomValue(0, 1) == 0)
			{
				posX = static_cast<float>(GetRandomValue(0, screenWidth));
				posY = 0 - size;
			}
			else
			{
				posX = static_cast<float>(GetRandomValue(0, screenWidth));
				posY = screenHeight + size;
			}
		}

		position = { posX, posY };
		return position;
	}

	Vector2 GetRandomDirection()
	{
		Vector2 dir{ 0,0 };
		float dirX;
		float dirY;
		do
		{
			dirX = static_cast<float>(GetRandomValue(-9, 9));
		} while (dirX < 3 && dirX > -3);
		do
		{
			dirY = static_cast<float>(GetRandomValue(-9, 9));
		} while (dirY < 3 && dirY > -3);
		dirX *= 0.1f;
		dirY *= 0.1f;

		dir = { dirX, dirY };
		Vector2Normalize(dir);

		return dir;
	}
}