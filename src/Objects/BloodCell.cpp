#include "Objects/BloodCell.h"

namespace asteroids
{
	void BloodCellCheckScreenBoundsCollision(BloodCell& bloodCell, float screenWidth, float screenHeight);


	void BloodCellsStart(BloodCell bloodCells[], int bloodCellsQty)
	{
		for (int i = 0; i < bloodCellsQty; i++)
		{
			bloodCells[i].isActive = false;
		}
	}

	static const float BLOODCELLS_SPAWN_RATE = 5.0f;
	static float timer;
	int activeBloodCells = 0;


	void BloodCellsUpdate(BloodCell bloodCells[], int bloodCellsQty)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());

		if (timer > BLOODCELLS_SPAWN_RATE && activeBloodCells < bloodCellsQty / 2)
		{
			timer = 0;
			for (int i = 0; i < bloodCellsQty; i++)
			{
				if (!bloodCells[i].isActive)
				{
					bloodCells[i].isActive = true;
					float posX;
					float posY;
					if (GetRandomValue(0, 1) == 0)
					{
						if (GetRandomValue(0, 1) == 0)
						{
							posX = 0 - bloodCells->size;
							posY = static_cast<float>(GetRandomValue(0, static_cast<int>(screenHeight)));
						}
						else
						{
							posX = screenHeight + bloodCells->size;
							posY = static_cast<float>(GetRandomValue(0, static_cast<int>(screenHeight)));
						}
					}
					else
					{
						if (GetRandomValue(0, 1) == 0)
						{
							posX = static_cast<float>(GetRandomValue(0, static_cast<int>(screenWidth)));
							posY = 0 - bloodCells->size;
						}
						else
						{
							posX = static_cast<float>(GetRandomValue(0, static_cast<int>(screenWidth)));
							posY = screenHeight + bloodCells->size;
						}
					}
					bloodCells[i].position = { posX, posY };

					float dirX;
					float dirY;
					do
					{
						dirX = static_cast<float>(GetRandomValue(-9, 9));
					} while (dirX < 3  && dirX > -3);
					do
					{
						dirY = static_cast<float>(GetRandomValue(-9, 9));
					} while (dirY < 3 && dirY > -3);
					dirX *= 0.1f;
					dirY *= 0.1f;

					bloodCells[i].dir = { dirX, dirY };
					Vector2Normalize(bloodCells[i].dir);
					break;
				}
			}
		}
		else
			timer += GetFrameTime();

		for (int i = 0; i < bloodCellsQty; i++)
		{
			if (bloodCells[i].isActive)
			{
				bloodCells[i].position = Vector2Add(bloodCells[i].position, Vector2Scale(bloodCells[i].dir, bloodCells[i].speed * GetFrameTime()));
				BloodCellCheckScreenBoundsCollision(bloodCells[i], screenWidth, screenHeight);
			}
		}
	}

	void BloodCellsDraw(BloodCell bloodCells[], int bloodCellsQty)
	{
		for (int i = 0; i < bloodCellsQty; i++)
		{
			if (bloodCells[i].isActive)
				DrawCircle(static_cast<int>(bloodCells[i].position.x), static_cast<int>(bloodCells[i].position.y), bloodCells[i].size, RED);
		}
	}

	void BloodCellsColliderDraw(BloodCell bloodCells[], int bloodCellsQty)
	{
		for (int i = 0; i < bloodCellsQty; i++)
		{
			if (bloodCells[i].isActive)
				DrawCircleLines(static_cast<int>(bloodCells[i].position.x), static_cast<int>(bloodCells[i].position.y), bloodCells[i].size, GREEN);
		}
	}

	void BloodCellCheckScreenBoundsCollision(BloodCell& bloodCell, float screenWidth, float screenHeight)
	{
		if (bloodCell.position.x + bloodCell.dir.x * bloodCell.speed * GetFrameTime() > screenWidth)
		{
			bloodCell.position.x = 0;
			if (bloodCell.dir.y > 0)
			{
				if (bloodCell.position.y > screenHeight / 2)
					bloodCell.position.y = screenHeight - bloodCell.position.y;
			}
			else if (bloodCell.dir.y < 0)
			{
				if (bloodCell.position.y < screenHeight / 2)
					bloodCell.position.y = screenHeight - bloodCell.position.y;
			}
		}
		else if (bloodCell.position.x + bloodCell.dir.x * bloodCell.speed * GetFrameTime() < 0)
		{
			bloodCell.position.x = screenWidth;
			if (bloodCell.dir.y > 0)
			{
				if (bloodCell.position.y > screenHeight / 2)
					bloodCell.position.y = screenHeight - bloodCell.position.y;
			}
			else if (bloodCell.dir.y < 0)
			{
				if (bloodCell.position.y < screenHeight / 2)
					bloodCell.position.y = screenHeight - bloodCell.position.y;
			}
		}

		if (bloodCell.position.y + bloodCell.dir.y * bloodCell.speed * GetFrameTime() > screenHeight)
		{
			bloodCell.position.y = 0;
			if (bloodCell.dir.x > 0)
			{
				if (bloodCell.position.x > screenWidth / 2)
					bloodCell.position.x = screenWidth - bloodCell.position.x;
			}
			else if (bloodCell.dir.x < 0)
			{
				if (bloodCell.position.x < screenWidth / 2)
					bloodCell.position.x = screenWidth - bloodCell.position.x;
			}
		}
		else if (bloodCell.position.y + bloodCell.dir.y * bloodCell.speed * GetFrameTime() < 0)
		{
			bloodCell.position.y = screenHeight;
			if (bloodCell.dir.x > 0)
			{
				if (bloodCell.position.x > screenWidth / 2)
					bloodCell.position.x = screenWidth - bloodCell.position.x;
			}
			else if (bloodCell.dir.x < 0)
			{
				if (bloodCell.position.x < screenWidth / 2)
					bloodCell.position.x = screenWidth - bloodCell.position.x;
			}
		}
	}
}
