#include "Objects/UI.h"

#include "GameManagement/ScreenManager.h"
#include <string>
using namespace std;

namespace asteroids
{
	void HudDraw(GameData& gd)
	{
		string playerLivesText = "Lives: " + to_string(gd.player.lives);
		DrawText(playerLivesText.c_str(), 0, 0, 40, WHITE);

		string patientHealth = "Patient Health: " + to_string(gd.patient.patientHealth);
		DrawText(patientHealth.c_str(), GetScreenWidth() - MeasureText(patientHealth.c_str(), 40), 0, 40, WHITE);
	}

	static int titleWindowLimitSpacing = 120;
	static int pressKeyWindowLimitSpacing = 120;
	static int wordsSpacing = 40;

	void PausePanelDraw()
	{
		const char* pauseTitle = "Game is Paused";
		int titleSize = static_cast<int>(120 * GetScreenScale());

		const char* backToMenuText = "Press Middle Click to go Continue Playing";
		int backToMenuSize = static_cast <int>(60 * GetScreenScale());
		DrawText(pauseTitle, GetScreenWidth() / 2 - MeasureText(pauseTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
		DrawText(backToMenuText, GetScreenWidth() / 2 - MeasureText(backToMenuText, backToMenuSize) / 2, GetScreenHeight() / 2, backToMenuSize, WHITE);
	}

	void RulesDraw()
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

	void GameOverPanelDraw()
	{
		const char* gameOverTitle = "Game Over";
		const char* backToMenuText = "Back to menu with Right Click";
		int titleSize = static_cast<int>(130 * GetScreenScale());
		int backToMenuSize = static_cast<int>(60 * GetScreenScale());

		DrawText(gameOverTitle, GetScreenWidth() / 2 - MeasureText(gameOverTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
		DrawText(backToMenuText, GetScreenWidth() / 2 - MeasureText(backToMenuText, backToMenuSize) / 2, GetScreenHeight() / 2, backToMenuSize, WHITE);
	}
}
