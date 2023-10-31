#include "Objects/WhiteBloodCells.h"

#include "GameManagement/AudioManager.h"
#include "GameManagement/TexturesManager.h"

namespace asteroids
{
	void VirusScreenBoundsCollision(WhiteCell& whiteCell, float screenWidth, float screenHeight);

	static const float WHITECELL_SPAWN_RATE = 5.0f;
	static float timer;
	int activeWhiteCells = 0;

	void WhiteCellStart(WhiteCell& whiteCell)
	{
		whiteCell.isActive = false;
	}

	void WhiteCellsSpawner(WhiteCell whiteCells[], int whiteCellsQty)
	{
		if (timer > WHITECELL_SPAWN_RATE && activeWhiteCells < whiteCellsQty / 4)
		{
			timer = 0;
			for (int i = 0; i < whiteCellsQty; i++)
			{
				if (!whiteCells[i].isActive)
				{
					whiteCells[i].isActive = true;
					whiteCells[i].phase = 1;

					whiteCells[i].normalSize = static_cast<float>(GetRandomValue(25, 70));
					whiteCells[i].smallSize = whiteCells[i].normalSize / 1.5f;
					whiteCells[i].miniSize = whiteCells[i].normalSize / 3.0f;
					whiteCells[i].currentSize = whiteCells[i].normalSize;
					whiteCells[i].speed = -whiteCells[i].speedMultiplier * whiteCells[i].currentSize + whiteCells[i].baseSpeed;
					whiteCells[i].baseSpeed = whiteCells[i].speed;

					whiteCells[i].position = GetRandomPosition(whiteCells[i].currentSize);
					whiteCells[i].dir = GetRandomDirection();
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
		whiteCell.angle += whiteCell.rotation * GetFrameTime();
	}

	float WHITE_CELL_TEXTURE_SIZE = 104;

	void WhiteCellDraw(WhiteCell& whiteCell)
	{
		if (whiteCell.isActive)
			DrawTexturePro(GetTexture(TextureIdentifier::WhiteCell), { 0,0, WHITE_CELL_TEXTURE_SIZE ,WHITE_CELL_TEXTURE_SIZE }, { whiteCell.position.x, whiteCell.position.y,whiteCell.currentSize * 2,whiteCell.currentSize * 2 }, { whiteCell.currentSize,whiteCell.currentSize }, whiteCell.angle, WHITE);
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
		whiteCell.isActive = true;
		whiteCell.position = position;
		whiteCell.dir = dir;

		if (whiteCell.phase == 1)
		{
			whiteCell.phase = 2;
			whiteCell.currentSize = whiteCell.smallSize;
			whiteCell.speed = whiteCell.speedMultiplier * whiteCell.baseSpeed;
			PlaySound(GetSound(SoundIdentifier::whiteCellExplosion));
		}
		else if (whiteCell.phase == 2)
		{
			whiteCell.phase = 3;
			whiteCell.currentSize = whiteCell.miniSize;
			whiteCell.speed = whiteCell.secondPhaseSpeedMultiplier * whiteCell.baseSpeed;
			PlaySound(GetSound(SoundIdentifier::whiteCellExplosion));
		}
		else
			WhiteCellDestroy(whiteCell);
	}

	void WhiteCellDestroy(WhiteCell& whiteCell)
	{
		PlaySound(GetSound(SoundIdentifier::whiteCellExplosion));

		if (whiteCell.isActive)
			whiteCell.isActive = false;

		activeWhiteCells--;

	}
}
