#include "GameManagement/Gameplay.h"

#include <string>

#include "Objects/Button.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"
#include "GameManagement/ScreenManager.h"
#include "GameManagement/CollisionManager.h"
#include "GameManagement/AsteroidsHandler.h"
#include "GameManagement/AudioManager.h"
#include "Objects/UI.h"

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
		ClearBackground(BLACK);
		PlayerDraw(gd.player);


		AsteroidsDraw(gd);
		for (Bullet& bullet : gd.player.bullets)
		{
			if (bullet.isActive)
				BulletDraw(bullet);
		}

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
			if (IsMouseButtonPressed(1))
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

		if (gd.areRulesBeingShown)
		{
			RulesDraw();
		}
		else if (gd.isGameOver)
		{
			GameOverPanelDraw();
		}
		else
		{
			PausePanelDraw();
		}
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
		ResetPlayer(gd.player);
	}
};