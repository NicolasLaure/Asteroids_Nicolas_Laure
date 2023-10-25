#include "GameManagement/Gameplay.h"

#include <string>

#include "Objects/Button.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"
#include "GameManagement/ScreenManager.h"
#include "GameManagement/CollisionManager.h"

using namespace std;

namespace asteroids
{
	static GameData gd;

	void GameStart();
	void GameUpdate();
	void GameDraw();

	void PauseUpdate(Scenes& scene);
	void PauseDraw();

	void ResetGameStats();

	void GameScene(bool enteredNewScene, Scenes& scene)
	{

		if (enteredNewScene || gd.justRestarted)
		{
			GameStart();
			gd.justRestarted = false;
		}

		if (!gd.isPaused)
		{
			GameUpdate();
			GameDraw();
		}
		else
		{
			PauseUpdate(scene);
			PauseDraw();
		}
	}

	void GameStart()
	{
		ResetGameStats();

		PlayerStart(gd.player);

		BulletsStart(gd.player.bullets, gd.player.BULLETS_QTY);

		//int buttonLimitSpacing = 50;
		//int buttonsSpacing = 100;
		//Vector2 textSize = { static_cast<float>(slGetTextWidth(gd.menuButton.text)), static_cast<float>(slGetTextHeight(gd.menuButton.text)) };
		//gd.menuButton.buttonRect = { { static_cast<float>(GetScreenWidth() / 2) - textSize.x / 2, 0.0f + buttonLimitSpacing }, textSize.x, textSize.y };

		//textSize = { static_cast<float>(slGetTextWidth(gd.restartButton.text)),static_cast<float>(slGetTextHeight(gd.restartButton.text)) };
		//gd.restartButton.buttonRect = { { static_cast<float>(GetScreenWidth() / 2) - textSize.x / 2, 0.0f + buttonLimitSpacing + buttonsSpacing }, textSize.x, textSize.y };
	}

	void GameUpdate()
	{
		if (IsMouseButtonPressed(2))
		{
			gd.isPaused = true;
		}

		PlayerUpdate(gd.player);
		int activeBullets = 0;
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
			{
				BulletUpdate(bullet);
				activeBullets++;
			}
		}
		BloodCellsUpdate(gd.bloodCells, gd.BLOOD_CELLS_QTY);
		VirusesUpdate(gd.viruses, gd.VIRUSES_QTY);

		CheckCollisions(gd);
	}

	void GameDraw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		PlayerDraw(gd.player);

		VirusesDraw(gd.viruses, gd.VIRUSES_QTY);
		BloodCellsDraw(gd.bloodCells, gd.BLOOD_CELLS_QTY);
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
				BulletDraw(bullet);
		}

#ifdef _DEBUG
		PlayerDrawCollider(gd.player);
		VirusesColliderDraw(gd.viruses, gd.VIRUSES_QTY);
		BloodCellsColliderDraw(gd.bloodCells, gd.BLOOD_CELLS_QTY);
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
				BulletColliderDraw(bullet);
		}
#endif // _DEBUG

		EndDrawing();
	}

	void PauseUpdate(Scenes& scene)
	{
		if (gd.areRulesBeingShown)
		{
			if (IsMouseButtonPressed(0))
			{
				gd.isPaused = false;
				gd.areRulesBeingShown = false;
			}
		}
		else if (gd.isGameOver || gd.hasWon)
		{
			ButtonCollisionCheck(gd.menuButton, scene);
			ResetButtonCollisionCheck(gd.restartButton, gd.justRestarted);
			if (IsMouseButtonPressed(2))
			{
				scene = Scenes::Menu;
			}
		}
		else
		{
			if (IsMouseButtonPressed(2))
			{
				gd.isPaused = false;
			}
		}
	}

	void PauseDraw()
	{
		BeginDrawing();

		ClearBackground(BLACK);
		Color panelColor = BLACK;

		if (!gd.areRulesBeingShown)
			panelColor = ColorAlpha(panelColor, 0.010f);

		DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight(), panelColor);

		int titleWindowLimitSpacing = 120;
		int pressKeyWindowLimitSpacing = 120;
		int wordsSpacing = 40;

		if (gd.areRulesBeingShown)
		{
			const char* rulesTitle = "Rules";
			int titleSize = static_cast<int>(150 * GetScreenScale());
			int rulesSize = static_cast<int>(40 * GetScreenScale());
			const char* winConditionText = "Destroy as many viruses as you can to set a new HighScore";
			const char* bloodCellsText = "But be careful, shooting at BloodCells might hurt the patient";
			const char* controlsTextLClick = "Left Click to Shoot";
			const char* controlsTextMClick = "Middle Click to Pause";
			const char* controlsTextRClick = "Right Click to Thrust";
			const char* pressAnyKeyText = "Click anywhere to start the game";

			DrawText(rulesTitle, GetScreenWidth() / 2 - MeasureText(rulesTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);

			DrawText(winConditionText, GetScreenWidth() / 2 - MeasureText(winConditionText, rulesSize) / 2, GetScreenHeight() / 2 - wordsSpacing, rulesSize, WHITE);
			DrawText(bloodCellsText, GetScreenWidth() / 2 - MeasureText(bloodCellsText, rulesSize) / 2, GetScreenHeight(), rulesSize, WHITE);
			DrawText(controlsTextLClick, GetScreenWidth() / 2 - MeasureText(controlsTextLClick, rulesSize) / 2, GetScreenHeight() / 2 + wordsSpacing, rulesSize, WHITE);
			DrawText(controlsTextMClick, GetScreenWidth() / 2 - MeasureText(controlsTextMClick, rulesSize) / 2, GetScreenHeight() / 2 + wordsSpacing * 2, rulesSize, WHITE);
			DrawText(controlsTextRClick, GetScreenWidth() / 2 - MeasureText(controlsTextRClick, rulesSize) / 2, GetScreenHeight() / 2 + wordsSpacing * 3, rulesSize, WHITE);

			DrawText(pressAnyKeyText, GetScreenWidth() / 2 - MeasureText(pressAnyKeyText, rulesSize) / 2, GetScreenHeight() - pressKeyWindowLimitSpacing, rulesSize, WHITE);
		}
		else if (gd.isGameOver)
		{
			const char* gameOverTitle = "Game Over";
			const char* backToMenuText = "Back to menu with Right Click";
			int titleSize = static_cast<int>(130 * GetScreenScale());
			int backToMenuSize = static_cast<int>(60 * GetScreenScale());

			DrawText(gameOverTitle, GetScreenWidth() / 2 - MeasureText(gameOverTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
			DrawText(backToMenuText, GetScreenWidth() / 2 - MeasureText(backToMenuText, backToMenuSize) / 2, GetScreenHeight() / 2, backToMenuSize, WHITE);
		}
		else
		{
			const char* pauseTitle = "Game is Paused";
			int titleSize = static_cast<int>(120 * GetScreenScale());

			const char* backToMenuText = "Press Middle Click to go Continue Playing";
			int backToMenuSize = static_cast <int>(60 * GetScreenScale());
			DrawText(pauseTitle, GetScreenWidth() / 2 - MeasureText(pauseTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
			DrawText(backToMenuText, GetScreenWidth() / 2 - MeasureText(backToMenuText, backToMenuSize) / 2, GetScreenHeight() / 2, backToMenuSize, WHITE);
		}
		EndDrawing();
	}

	void ResetGameStats()
	{
		gd.score = 0;
		gd.isGameOver = false;
		gd.lives = gd.maxLives;
		gd.hasWon = false;
		gd.isPaused = true;
		gd.areRulesBeingShown = true;

		ResetPlayer(gd.player);
	}

};