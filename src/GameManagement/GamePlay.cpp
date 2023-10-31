#include "GameManagement/Gameplay.h"

#include "Objects/Button.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"
#include "GameManagement/ScreenManager.h"
#include "GameManagement/CollisionManager.h"
#include "GameManagement/AsteroidsHandler.h"
#include "GameManagement/AudioManager.h"
#include "GameManagement/PowerUpsManager.h"
#include "Objects/UI.h"

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

			if (enteredNewScene)
				PlayMusicStream(GetMusic(MusicIdentifier::GamePlayMusic));
		}

		if (gd.isGameOver || gd.hasWon)
			gd.isPaused = true;
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
		AsteroidsStart(gd);
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
		AsteroidsUpdate(gd);

		CheckCollisions(gd);

		UpdateMusicStream(GetMusic(MusicIdentifier::GamePlayMusic));
	}

	void GameDraw()
	{
		BeginDrawing();
		Color bgColor = { 99,11,11,255 };
		ClearBackground(bgColor);

		AsteroidsDraw(gd);
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
				BulletDraw(bullet);
		}
		PlayerDraw(gd.player);

		DrawPowerUps(gd.powerUps, gd.POWERUPS_QTY);

#ifdef _DEBUG
		PlayerDrawCollider(gd.player);
		AsteroidsDebugDraw(gd);
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
				BulletColliderDraw(bullet);
		}
#endif // _DEBUG
		HudDraw(gd);
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
			ButtonCollisionCheck(gd.menuButton, scene);
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

		if (gd.areRulesBeingShown)
			RulesDraw();
		else if (gd.isGameOver || gd.hasWon)
			GameOverPanelDraw(gd.menuButton, gd.restartButton, gd.hasWon);
		else
			PausePanelDraw(gd.menuButton);

		EndDrawing();
	}

	void ResetGameStats()
	{
		gd.score = 0;
		gd.isGameOver = false;
		gd.hasWon = false;
		gd.isPaused = true;
		gd.areRulesBeingShown = true;
		gd.patient.patientHealth = 100;

		PowerUpsReset(gd.powerUps, gd.POWERUPS_QTY);
		AsteroidsStart(gd);
		ResetPlayer(gd.player);
	}
};