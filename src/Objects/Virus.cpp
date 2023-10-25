#include "Objects/Virus.h"

namespace asteroids
{

	void VirusScreenBoundsCollision(Virus& virus, float screenWidth, float screenHeight);

	void VirusesStart(Virus viruses[], int virusesQty)
	{
		for (int i = 0; i < virusesQty; i++)
		{
			viruses[i].isActive = false;
		}
	}

	static const float VIRUS_SPAWN_RATE = 5.0f;
	static float timer;
	int activeViruses = 0;

	void VirusesUpdate(Virus viruses[], int virusesQty)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());

		if (timer > VIRUS_SPAWN_RATE && activeViruses < virusesQty / 4)
		{
			timer = 0;
			for (int i = 0; i < virusesQty; i++)
			{
				if (!viruses[i].isActive)
				{
					viruses[i].isActive = true;
					viruses[i].phase = 1;
					viruses[i].currentSize = viruses[i].normalSize;
					float posX;
					float posY;
					if (GetRandomValue(0, 1) == 0)
					{
						if (GetRandomValue(0, 1) == 0)
						{
							posX = 0 - viruses->currentSize;
							posY = static_cast<float>(GetRandomValue(0, static_cast<int>(screenHeight)));
						}
						else
						{
							posX = screenHeight + viruses->currentSize;
							posY = static_cast<float>(GetRandomValue(0, static_cast<int>(screenHeight)));
						}
					}
					else
					{
						if (GetRandomValue(0, 1) == 0)
						{
							posX = static_cast<float>(GetRandomValue(0, static_cast<int>(screenWidth)));
							posY = 0 - viruses->currentSize;
						}
						else
						{
							posX = static_cast<float>(GetRandomValue(0, static_cast<int>(screenWidth)));
							posY = screenHeight + viruses->currentSize;
						}
					}
					viruses[i].position = { posX, posY };

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

					viruses[i].dir = { dirX, dirY };
					Vector2Normalize(viruses[i].dir);
					break;
				}
			}
		}
		else
			timer += GetFrameTime();

		for (int i = 0; i < virusesQty; i++)
		{
			if (viruses[i].isActive)
			{
				viruses[i].position = Vector2Add(viruses[i].position, Vector2Scale(viruses[i].dir, viruses[i].speed * GetFrameTime()));
				VirusScreenBoundsCollision(viruses[i], screenWidth, screenHeight);
			}
		}
	}

	void VirusesDraw(Virus viruses[], int virusesQty)
	{
		for (int i = 0; i < virusesQty; i++)
		{
			if (viruses[i].isActive)
				DrawCircle(static_cast<int>(viruses[i].position.x), static_cast<int>(viruses[i].position.y), viruses[i].currentSize, DARKGREEN);
		}
	}

	void VirusesColliderDraw(Virus viruses[], int virusesQty)
	{
		for (int i = 0; i < virusesQty; i++)
		{
			if (viruses[i].isActive)
				DrawCircleLines(static_cast<int>(viruses[i].position.x), static_cast<int>(viruses[i].position.y), viruses[i].currentSize, GREEN);
		}
	}

	void VirusScreenBoundsCollision(Virus& virus, float screenWidth, float screenHeight)
	{
		if (virus.position.x + virus.dir.x * virus.speed * GetFrameTime() > screenWidth)
		{
			virus.position.x = 0;
			if (virus.dir.y > 0)
			{
				if (virus.position.y > screenHeight / 2)
					virus.position.y = screenHeight - virus.position.y;
			}
			else if (virus.dir.y < 0)
			{
				if (virus.position.y < screenHeight / 2)
					virus.position.y = screenHeight - virus.position.y;
			}
		}
		else if (virus.position.x + virus.dir.x * virus.speed * GetFrameTime() < 0)
		{
			virus.position.x = screenWidth;
			if (virus.dir.y > 0)
			{
				if (virus.position.y > screenHeight / 2)
					virus.position.y = screenHeight - virus.position.y;
			}
			else if (virus.dir.y < 0)
			{
				if (virus.position.y < screenHeight / 2)
					virus.position.y = screenHeight - virus.position.y;
			}
		}

		if (virus.position.y + virus.dir.y * virus.speed * GetFrameTime() > screenHeight)
		{
			virus.position.y = 0;
			if (virus.dir.x > 0)
			{
				if (virus.position.x > screenWidth / 2)
					virus.position.x = screenWidth - virus.position.x;
			}
			else if (virus.dir.x < 0)
			{
				if (virus.position.x < screenWidth / 2)
					virus.position.x = screenWidth - virus.position.x;
			}
		}
		else if (virus.position.y + virus.dir.y * virus.speed * GetFrameTime() < 0)
		{
			virus.position.y = screenHeight;
			if (virus.dir.x > 0)
			{
				if (virus.position.x > screenWidth / 2)
					virus.position.x = screenWidth - virus.position.x;
			}
			else if (virus.dir.x < 0)
			{
				if (virus.position.x < screenWidth / 2)
					virus.position.x = screenWidth - virus.position.x;
			}
		}
	}
}
