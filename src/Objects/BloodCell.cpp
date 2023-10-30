#include "Objects/BloodCell.h"

namespace asteroids
{
	void BloodCellCheckScreenBoundsCollision(BloodCell& bloodCell, float screenWidth, float screenHeight);

	void BloodCellStart(BloodCell& bloodCell)
	{
		bloodCell.isActive = false;
		bloodCell.normalSize = 60;
		bloodCell.currentSize = bloodCell.normalSize;
	}

	static const float BLOODCELLS_SPAWN_RATE = 3.0f;
	static float timer;
	int activeBloodCells = 0;

	void BloodCellsSpawner(BloodCell bloodCells[], int bloodCellsQty)
	{
		if (timer > BLOODCELLS_SPAWN_RATE && activeBloodCells < bloodCellsQty / 4)
		{
			timer = 0;
			for (int i = 0; i < bloodCellsQty; i++)
			{
				if (!bloodCells[i].isActive)
				{
					bloodCells[i].isActive = true;
					bloodCells[i].phase = 1;

					bloodCells[i].normalSize = static_cast<float>(GetRandomValue(25, 70));
					bloodCells[i].smallSize = bloodCells[i].normalSize / 1.5f;
					bloodCells[i].miniSize = bloodCells[i].normalSize / 3.0f;
					bloodCells[i].currentSize = bloodCells[i].normalSize;
					bloodCells[i].speed = -bloodCells[i].speedMultiplier * bloodCells[i].currentSize + bloodCells[i].baseSpeed;
					bloodCells[i].baseSpeed = bloodCells[i].speed;

					bloodCells[i].position = GetRandomPosition(bloodCells[i].currentSize);
					bloodCells[i].dir = GetRandomDirection();
					break;
				}
			}
		}
		else
			timer += GetFrameTime();
	}

	void BloodCellUpdate(BloodCell& bloodCell)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());
		if (bloodCell.isActive)
		{
			bloodCell.position = Vector2Add(bloodCell.position, Vector2Scale(bloodCell.dir, bloodCell.speed * GetFrameTime()));
			BloodCellCheckScreenBoundsCollision(bloodCell, screenWidth, screenHeight);
		}
	}

	void BloodCellDraw(BloodCell& bloodCell)
	{
		if (bloodCell.isActive)
			DrawCircle(static_cast<int>(bloodCell.position.x), static_cast<int>(bloodCell.position.y), bloodCell.currentSize, RED);
	}

	void BloodCellColliderDraw(BloodCell& bloodCell)
	{
		if (bloodCell.isActive)
			DrawCircleLines(static_cast<int>(bloodCell.position.x), static_cast<int>(bloodCell.position.y), bloodCell.currentSize, GREEN);
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

	void BloodCellDivision(BloodCell& bloodCell, Vector2 position, Vector2 dir)
	{
		bloodCell.isActive = true;
		bloodCell.position = position;
		bloodCell.dir = dir;

		if (bloodCell.phase == 1)
		{
			bloodCell.phase = 2;
			bloodCell.currentSize = bloodCell.smallSize;
			bloodCell.speed = bloodCell.speedMultiplier * bloodCell.baseSpeed;
		}
		else if (bloodCell.phase == 2)
		{
			bloodCell.phase = 3;
			bloodCell.currentSize = bloodCell.miniSize;
			bloodCell.speed = bloodCell.secondPhaseSpeedMultiplier * bloodCell.baseSpeed;
		}
		else
			BloodCellDestroy(bloodCell);
	}

	void BloodCellDestroy(BloodCell& bloodCell)
	{
		if (bloodCell.isActive)
			bloodCell.isActive = false;

		activeBloodCells--;
	}
}
