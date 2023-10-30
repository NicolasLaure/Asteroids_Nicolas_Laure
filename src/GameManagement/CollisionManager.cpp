#include "GameManagement/CollisionManager.h"

#include "Objects/Patient.h"

namespace asteroids
{
	void BulletBloodCellCollision(GameData& gd, BloodCell& bloodCell, Bullet& bullet);
	void BulletWhiteCellCollision(GameData& gd, WhiteCell& whiteCell, Bullet& bullet);
	void PlayerWhiteCellCollision(WhiteCell& whiteCell, Player& player, bool& isGameOver);
	void PlayerBloodCellCollision(GameData& gd, BloodCell& bloodCell);

	void CheckCollisions(GameData& gd)
	{
		for (int i = 0; i < gd.player.BULLETS_QTY; i++)
		{
			if (gd.player.bullets[i].isActive)
			{
				for (int j = 0; j < gd.BLOOD_CELLS_QTY; j++)
				{
					if (gd.bloodCells[j].isActive)
						BulletBloodCellCollision(gd, gd.bloodCells[j], gd.player.bullets[i]);
				}
				for (int j = 0; j < gd.WHITECELLS_QTY; j++)
				{
					if (gd.whiteCells[j].isActive)
						BulletWhiteCellCollision(gd, gd.whiteCells[j], gd.player.bullets[i]);
				}
			}
		}
		for (int i = 0; i < gd.WHITECELLS_QTY; i++)
		{
			if (gd.whiteCells[i].isActive)
			{
				PlayerWhiteCellCollision(gd.whiteCells[i], gd.player, gd.isGameOver);
			}
		}
		for (int i = 0; i < gd.BLOOD_CELLS_QTY; i++)
		{
			if (gd.bloodCells[i].isActive)
			{
				PlayerBloodCellCollision(gd, gd.bloodCells[i]);
			}
		}
	}

	void BulletBloodCellCollision(GameData& gd, BloodCell& bloodCell, Bullet& bullet)
	{
		Vector2 bulletPosition = { bullet.position.x + bullet.size / 2, bullet.position.y + bullet.size / 2 };

		float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(bloodCell.position.x) - bulletPosition.x, 2) + pow(static_cast<double>(bloodCell.position.y) - bulletPosition.y, 2)));

		if (distanceBetweenCircles <= bloodCell.currentSize + bullet.size)
		{
			bullet.isActive = false;
			Vector2 newDir = { bullet.direction.y * -1, bullet.direction.x };
			Vector2 newDirInverted = { bullet.direction.y, bullet.direction.x * -1 };

			for (int k = 0; k < gd.WHITECELLS_QTY; k++)
			{
				if (!gd.bloodCells[k].isActive)
				{
					gd.bloodCells[k].smallSize = bloodCell.smallSize;
					gd.bloodCells[k].miniSize = bloodCell.miniSize;
					gd.bloodCells[k].phase = bloodCell.phase;
					gd.bloodCells[k].baseSpeed = bloodCell.baseSpeed;

					BloodCellDivision(bloodCell, bloodCell.position, newDir);
					BloodCellDivision(gd.bloodCells[k], bloodCell.position, newDirInverted);
					break;
				}
			}
			PatientTakeDamage(gd.patient, gd.hasWon);
		}
	}

	void BulletWhiteCellCollision(GameData& gd, WhiteCell& whiteCell, Bullet& bullet)
	{
		Vector2 bulletPosition = { bullet.position.x + bullet.size / 2, bullet.position.y + bullet.size / 2 };

		float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(whiteCell.position.x) - bulletPosition.x, 2) + pow(static_cast<double>(whiteCell.position.y) - bulletPosition.y, 2)));

		if (distanceBetweenCircles <= whiteCell.currentSize + bullet.size)
		{
			bullet.isActive = false;
			Vector2 newDir = { bullet.direction.y * -1, bullet.direction.x };
			Vector2 newDirInverted = { bullet.direction.y, bullet.direction.x * -1 };

			for (int k = 0; k < gd.WHITECELLS_QTY; k++)
			{
				if (!gd.whiteCells[k].isActive)
				{
					gd.whiteCells[k].smallSize = whiteCell.smallSize;
					gd.whiteCells[k].miniSize = whiteCell.miniSize;
					gd.whiteCells[k].phase = whiteCell.phase;
					gd.whiteCells[k].baseSpeed = whiteCell.baseSpeed;

					WhiteCellDivision(whiteCell, whiteCell.position, newDir);
					WhiteCellDivision(gd.whiteCells[k], whiteCell.position, newDirInverted);
					break;
				}
			}
		}
	}

	void PlayerWhiteCellCollision(WhiteCell& whiteCell, Player& player, bool& isGameOver)
	{
		float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(whiteCell.position.x) - player.position.x, 2) + pow(static_cast<double>(whiteCell.position.y) - player.position.y, 2)));

		if (distanceBetweenCircles <= player.colliderRadius + whiteCell.currentSize)
		{
			whiteCell.isActive = false;
			TakeDamage(player, isGameOver);
		}
	}

	void PlayerBloodCellCollision(GameData& gd, BloodCell& bloodCell)
	{
		float distanceBetweenCircles = static_cast<float>(sqrt(pow(static_cast<double>(bloodCell.position.x) - gd.player.position.x, 2) + pow(static_cast<double>(bloodCell.position.y) - gd.player.position.y, 2)));

		if (distanceBetweenCircles <= gd.player.colliderRadius + bloodCell.currentSize)
		{
			bloodCell.isActive = false;
			TakeDamage(gd.player, gd.isGameOver);
			PatientTakeDamage(gd.patient, gd.hasWon);
		}
	}
}