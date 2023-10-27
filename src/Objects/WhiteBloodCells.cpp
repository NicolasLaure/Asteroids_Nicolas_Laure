#include "Objects/WhiteBloodCells.h"

namespace asteroids
{

	void VirusScreenBoundsCollision(WhiteCell& whiteCell, float screenWidth, float screenHeight);

	void WhiteCellsStart(WhiteCell whiteCells[], int whiteCellsQty)
	{
		for (int i = 0; i < whiteCellsQty; i++)
		{
			whiteCells[i].isActive = false;
		}
	}

	static const float WHITECELL_SPAWN_RATE = 5.0f;
	static float timer;
	int activeWhiteCells = 0;

	void WhiteCellsUpdate(WhiteCell whiteCells[], int whiteCellsQty)
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
					whiteCells[i].currentSize = whiteCells[i].normalSize;
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

		for (int i = 0; i < whiteCellsQty; i++)
		{
			if (whiteCells[i].isActive)
			{
				whiteCells[i].position = Vector2Add(whiteCells[i].position, Vector2Scale(whiteCells[i].dir, whiteCells[i].speed * GetFrameTime()));
				VirusScreenBoundsCollision(whiteCells[i], screenWidth, screenHeight);
			}
		}
	}

	void WhiteCellsDraw(WhiteCell whiteCells[], int whiteCellsQty)
	{
		for (int i = 0; i < whiteCellsQty; i++)
		{
			if (whiteCells[i].isActive)
				DrawCircle(static_cast<int>(whiteCells[i].position.x), static_cast<int>(whiteCells[i].position.y), whiteCells[i].currentSize, WHITE);
		}
	}

	void WhiteCellsColliderDraw(WhiteCell whiteCells[], int whiteCellsQty)
	{
		for (int i = 0; i < whiteCellsQty; i++)
		{
			if (whiteCells[i].isActive)
				DrawCircleLines(static_cast<int>(whiteCells[i].position.x), static_cast<int>(whiteCells[i].position.y), whiteCells[i].currentSize, GREEN);
		}
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
}
