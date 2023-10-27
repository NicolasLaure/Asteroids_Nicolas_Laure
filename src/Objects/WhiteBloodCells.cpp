#include "Objects/WhiteBloodCells.h"

namespace asteroids
{
	void VirusScreenBoundsCollision(WhiteCell& whiteCell, float screenWidth, float screenHeight);
	void WhiteCellDestroy(WhiteCell& whiteCell);

	static const float WHITECELL_SPAWN_RATE = 5.0f;
	static float timer;
	int activeWhiteCells = 0;

	void WhiteCellStart(WhiteCell& whiteCell)
	{
		whiteCell.isActive = false;
	}

	void WhiteCellsSpawner(WhiteCell whiteCells[], int whiteCellsQty)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());

		if (timer > WHITECELL_SPAWN_RATE && activeWhiteCells < whiteCellsQty / 4)
		{
			timer = 0;
			for (int i = 0; i < whiteCellsQty; i++)
			{
				if (!whiteCells[i].isActive)
				{
					whiteCells[i].isActive = true;
					whiteCells[i].phase = 1;

					whiteCells[i].normalSize = static_cast<float>(GetRandomValue(15, 70));
					whiteCells[i].smallSize = whiteCells[i].normalSize / 1.5f;
					whiteCells[i].miniSize = whiteCells[i].normalSize / 3.0f;
					whiteCells[i].currentSize = whiteCells[i].normalSize;
					whiteCells[i].speed = -1.25f * whiteCells[i].currentSize + whiteCells[i].baseSpeed;

					float posX;
					float posY;
					if (GetRandomValue(0, 1) == 0)
					{
						if (GetRandomValue(0, 1) == 0)
						{
							posX = 0 - whiteCells->currentSize;
							posY = static_cast<float>(GetRandomValue(0, static_cast<int>(screenHeight)));
						}
						else
						{
							posX = screenHeight + whiteCells->currentSize;
							posY = static_cast<float>(GetRandomValue(0, static_cast<int>(screenHeight)));
						}
					}
					else
					{
						if (GetRandomValue(0, 1) == 0)
						{
							posX = static_cast<float>(GetRandomValue(0, static_cast<int>(screenWidth)));
							posY = 0 - whiteCells->currentSize;
						}
						else
						{
							posX = static_cast<float>(GetRandomValue(0, static_cast<int>(screenWidth)));
							posY = screenHeight + whiteCells->currentSize;
						}
					}
					whiteCells[i].position = { posX, posY };

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

					whiteCells[i].dir = { dirX, dirY };
					Vector2Normalize(whiteCells[i].dir);
					break;
				}
			}
		}
		else
			timer += GetFrameTime();


	}

	void WhiteCellUpdate(WhiteCell& whiteCell)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());
		if (whiteCell.isActive)
		{
			whiteCell.position = Vector2Add(whiteCell.position, Vector2Scale(whiteCell.dir, whiteCell.speed * GetFrameTime()));
			VirusScreenBoundsCollision(whiteCell, screenWidth, screenHeight);
		}
	}

	void WhiteCellDraw(WhiteCell& whiteCell)
	{
		if (whiteCell.isActive)
			DrawCircle(static_cast<int>(whiteCell.position.x), static_cast<int>(whiteCell.position.y), whiteCell.currentSize, WHITE);
	}

	void WhiteCellColliderDraw(WhiteCell& whiteCell)
	{
		if (whiteCell.isActive)
			DrawCircleLines(static_cast<int>(whiteCell.position.x), static_cast<int>(whiteCell.position.y), whiteCell.currentSize, GREEN);
	}

	void VirusScreenBoundsCollision(WhiteCell& whiteCell, float screenWidth, float screenHeight)
	{
		if (whiteCell.position.x + whiteCell.dir.x * whiteCell.speed * GetFrameTime() > screenWidth)
		{
			whiteCell.position.x = 0;
			if (whiteCell.dir.y > 0)
			{
				if (whiteCell.position.y > screenHeight / 2)
					whiteCell.position.y = screenHeight - whiteCell.position.y;
			}
			else if (whiteCell.dir.y < 0)
			{
				if (whiteCell.position.y < screenHeight / 2)
					whiteCell.position.y = screenHeight - whiteCell.position.y;
			}
		}
		else if (whiteCell.position.x + whiteCell.dir.x * whiteCell.speed * GetFrameTime() < 0)
		{
			whiteCell.position.x = screenWidth;
			if (whiteCell.dir.y > 0)
			{
				if (whiteCell.position.y > screenHeight / 2)
					whiteCell.position.y = screenHeight - whiteCell.position.y;
			}
			else if (whiteCell.dir.y < 0)
			{
				if (whiteCell.position.y < screenHeight / 2)
					whiteCell.position.y = screenHeight - whiteCell.position.y;
			}
		}

		if (whiteCell.position.y + whiteCell.dir.y * whiteCell.speed * GetFrameTime() > screenHeight)
		{
			whiteCell.position.y = 0;
			if (whiteCell.dir.x > 0)
			{
				if (whiteCell.position.x > screenWidth / 2)
					whiteCell.position.x = screenWidth - whiteCell.position.x;
			}
			else if (whiteCell.dir.x < 0)
			{
				if (whiteCell.position.x < screenWidth / 2)
					whiteCell.position.x = screenWidth - whiteCell.position.x;
			}
		}
		else if (whiteCell.position.y + whiteCell.dir.y * whiteCell.speed * GetFrameTime() < 0)
		{
			whiteCell.position.y = screenHeight;
			if (whiteCell.dir.x > 0)
			{
				if (whiteCell.position.x > screenWidth / 2)
					whiteCell.position.x = screenWidth - whiteCell.position.x;
			}
			else if (whiteCell.dir.x < 0)
			{
				if (whiteCell.position.x < screenWidth / 2)
					whiteCell.position.x = screenWidth - whiteCell.position.x;
			}
		}
	}

	void WhiteCellDivision(WhiteCell& whiteCell, Vector2 position, Vector2 dir)
	{
		if (whiteCell.phase == 1)
		{
			whiteCell.phase = 2;
			whiteCell.currentSize = whiteCell.smallSize;
		}
		else if (whiteCell.phase == 2)
		{
			whiteCell.phase = 3;
			whiteCell.currentSize = whiteCell.miniSize;
		}
		else
			WhiteCellDestroy(whiteCell);

		whiteCell.isActive = true;
		whiteCell.position = position;
		whiteCell.dir = dir;
		whiteCell.speed = -1.25f * whiteCell.currentSize + whiteCell.baseSpeed;
	}

	void WhiteCellDestroy(WhiteCell& whiteCell)
	{
		if (whiteCell.isActive)
			whiteCell.isActive = false;

		activeWhiteCells--;
	}
}
