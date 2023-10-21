#include "GameManagement/Gameplay.h"

#include <string>

#include "Objects/Button.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"

using namespace std;

namespace asteroids
{
	static GameData gd;

	void GameStart();
	void GameUpdate();
	void GameDraw();

	void PauseUpdate(Scenes& scene);
	void PauseDraw();


	void CollisionUpdate();
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
	}

	void GameDraw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		PlayerDraw(gd.player);

		//VirusesDraw(gd.viruses);
		//BloodCellsDraw(gd.bloodCells);
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
				BulletDraw(bullet);
		}

#ifdef _DEBUG
		PlayerDrawCollider(gd.player);
		//VirusesColliderDraw(gd.viruses);
		//BloodCellsColliderDraw(gd.bloodCells);
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

		//int titleWindowLimitSpacing = 120;
		//int pressKeyWindowLimitSpacing = 120;

		if (gd.areRulesBeingShown)
		{
			/*const char* rulesTitle = "Rules";
			int titleSize = 150;
			int rulesSize = 40;
			const char* winConditionText = "Destroy all bricks to win";
			const char* controlsText = "Left Click to shoot / Right Click to pause";
			const char* pressAnyKeyText = "Click anywhere to start the game";

			int rulesPositionY = GetScreenHeight() / 2 + 75;
			slSetForeColor(colorsData.WHITE.r, colorsData.WHITE.g, colorsData.WHITE.b, 1);
			slSetFontSize(titleSize);
			slText(GetScreenWidth() / 2 - slGetTextWidth(rulesTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, rulesTitle);
			slSetFontSize(rulesSize);
			slText(GetScreenWidth() / 2 - slGetTextWidth(winConditionText) / 2, rulesPositionY, winConditionText);
			slText(GetScreenWidth() / 2 - slGetTextWidth(controlsText) / 2, GetScreenHeight() / 2, controlsText);
			slText(GetScreenWidth() / 2 - slGetTextWidth(pressAnyKeyText) / 2, 0 + pressKeyWindowLimitSpacing, pressAnyKeyText);*/
		}
		else if (gd.isGameOver)
		{
			/*const char* gameOverTitle = "Game Over";
			int titleSize = 130;

			int rulesPositionY = GetScreenHeight() / 2 + 50;
			slSetForeColor(colorsData.WHITE.r, colorsData.WHITE.g, colorsData.WHITE.b, 1);
			slSetFontSize(titleSize);
			slText(GetScreenWidth() / 2 - slGetTextWidth(gameOverTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, gameOverTitle);

			slSetFontSize(gd.buttonsFontSize);
			slSetForeColor(gd.menuButton.currentTextColor.r, gd.menuButton.currentTextColor.g, gd.menuButton.currentTextColor.b, 1);
			slText(gd.menuButton.buttonRect.position.x, gd.menuButton.buttonRect.position.y, gd.menuButton.text);

			slSetForeColor(gd.restartButton.currentTextColor.r, gd.restartButton.currentTextColor.g, gd.restartButton.currentTextColor.b, 1);
			slText(gd.restartButton.buttonRect.position.x, gd.restartButton.buttonRect.position.y, gd.restartButton.text);*/
		}
		else if (gd.hasWon)
		{
			/*const char* gameOverTitle = "You Win!";
			int titleSize = 130;

			int gameOverSize = 40;

			string scoreText = "Score: " + to_string(gd.score);
			string highScore = "High Score: " + to_string(gd.highScore);

			int rulesPositionY = GetScreenHeight() / 2 + 50;
			slSetForeColor(colorsData.WHITE.r, colorsData.WHITE.g, colorsData.WHITE.b, 1);
			slSetFontSize(titleSize);
			slText(GetScreenWidth() / 2 - slGetTextWidth(gameOverTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, gameOverTitle);
			slSetFontSize(gameOverSize);

			int scoresOffset = 40;
			slText(GetScreenWidth() / 2 - slGetTextWidth(scoreText.c_str()) / 2, GetScreenHeight() / 2 - scoresOffset, scoreText.c_str());
			slText(GetScreenWidth() / 2 - slGetTextWidth(highScore.c_str()) / 2, GetScreenHeight() / 2 + scoresOffset, highScore.c_str());

			slSetFontSize(gd.buttonsFontSize);
			slSetForeColor(gd.menuButton.currentTextColor.r, gd.menuButton.currentTextColor.g, gd.menuButton.currentTextColor.b, 1);
			slText(gd.menuButton.buttonRect.position.x, gd.menuButton.buttonRect.position.y, gd.menuButton.text);

			slSetForeColor(gd.restartButton.currentTextColor.r, gd.restartButton.currentTextColor.g, gd.restartButton.currentTextColor.b, 1);
			slText(gd.restartButton.buttonRect.position.x, gd.restartButton.buttonRect.position.y, gd.restartButton.text);*/
		}
		else
		{
			/*const char* pauseTitle = "Game is Paused";
			int titleSize = 80;

			const char* backToMenuText = "Press Right click to go Unpause";
			int backToMenuSize = 40;*/

			/*slSetForeColor(colorsData.WHITE.r, colorsData.WHITE.g, colorsData.WHITE.b, 1);
			slSetFontSize(titleSize);
			slText(GetScreenWidth() / 2 - slGetTextWidth(pauseTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing - slGetTextHeight(pauseTitle) / 2, pauseTitle);
			slSetFontSize(backToMenuSize);
			slText(GetScreenWidth() / 2 - slGetTextWidth(backToMenuText) / 2, GetScreenHeight() / 2, backToMenuText);

			slSetFontSize(gd.buttonsFontSize);
			slSetForeColor(gd.menuButton.currentTextColor.r, gd.menuButton.currentTextColor.g, gd.menuButton.currentTextColor.b, 1);
			slText(gd.menuButton.buttonRect.position.x, gd.menuButton.buttonRect.position.y, gd.menuButton.text);

			slSetForeColor(gd.restartButton.currentTextColor.r, gd.restartButton.currentTextColor.g, gd.restartButton.currentTextColor.b, 1);
			slText(gd.restartButton.buttonRect.position.x, gd.restartButton.buttonRect.position.y, gd.restartButton.text);*/
		}
		EndDrawing();
	}

	void CollisionUpdate()
	{

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