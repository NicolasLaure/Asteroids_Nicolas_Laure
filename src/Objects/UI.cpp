#include "Objects/UI.h"

#include "GameManagement/ScreenManager.h"
#include "Objects/Button.h"
#include <string>
using namespace std;

namespace asteroids
{
	static int titleWindowLimitSpacing = 60;
	static int pressKeyWindowLimitSpacing = 120;
	static int wordsSpacing = 40;

	void HudDraw(GameData& gd)
	{
		string playerLivesText = "Lives: " + to_string(gd.player.lives);
		DrawText(playerLivesText.c_str(), 0, 0, 40, WHITE);

		string patientHealth = "Patient Health: " + to_string(gd.patient.patientHealth);
		DrawText(patientHealth.c_str(), GetScreenWidth() - MeasureText(patientHealth.c_str(), 40), 0, 40, WHITE);
	}

	void RulesDraw()
	{
		const char* rulesTitle = "Rules";
		int titleSize = static_cast<int>(150 * GetScreenScale());
		int rulesSize = static_cast<int>(40 * GetScreenScale());
		const char* winConditionText = "Destroy Blood Cells to weaken the target";
		const char* whiteCellsText = "But be careful, white cells will damage you";
		const char* whiteCellsText2 = "and some will pursue you";
		const char* controlsTextLClick = "Left Click to Shoot";
		const char* controlsTextMClick = "Middle Click to Pause";
		const char* controlsTextRClick = "Right Click to Thrust";
		const char* pressAnyKeyText = "Click anywhere to start the game";

		DrawText(rulesTitle, GetScreenWidth() / 2 - MeasureText(rulesTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);

		DrawText(winConditionText, GetScreenWidth() / 2 - MeasureText(winConditionText, rulesSize) / 2, GetScreenHeight() / 2 - wordsSpacing * 3, rulesSize, WHITE);
		DrawText(whiteCellsText, GetScreenWidth() / 2 - MeasureText(whiteCellsText, rulesSize) / 2, GetScreenHeight() / 2 - wordsSpacing * 2, rulesSize, WHITE);
		DrawText(whiteCellsText2, GetScreenWidth() / 2 - MeasureText(whiteCellsText2, rulesSize) / 2, GetScreenHeight() / 2 - wordsSpacing, rulesSize, WHITE);
		DrawText(controlsTextLClick, GetScreenWidth() / 2 - MeasureText(controlsTextLClick, rulesSize) / 2, GetScreenHeight() / 2 + wordsSpacing, rulesSize, WHITE);
		DrawText(controlsTextMClick, GetScreenWidth() / 2 - MeasureText(controlsTextMClick, rulesSize) / 2, GetScreenHeight() / 2 + wordsSpacing * 2, rulesSize, WHITE);
		DrawText(controlsTextRClick, GetScreenWidth() / 2 - MeasureText(controlsTextRClick, rulesSize) / 2, GetScreenHeight() / 2 + wordsSpacing * 3, rulesSize, WHITE);

		DrawText(pressAnyKeyText, GetScreenWidth() / 2 - MeasureText(pressAnyKeyText, rulesSize) / 2, GetScreenHeight() - pressKeyWindowLimitSpacing, rulesSize, WHITE);
	}

	void PausePanelDraw(Button& menuButton)
	{
		Color panelColor = { 60,60,60,255 };
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), panelColor);
		const char* pauseTitle = "Game is Paused";
		int titleSize = static_cast<int>(120 * GetScreenScale());

		const char* resumeText = "Press Middle Click to go resume Game";
		int resumeTextSize = static_cast <int>(60 * GetScreenScale());

		int buttonsSpacing = 30;

		menuButton.buttonRect.position = { static_cast<float>(GetScreenWidth()) / 2 - MeasureText(menuButton.text, menuButton.fontSize) / 2 , static_cast<float>(GetScreenHeight()) / 2 + buttonsSpacing };
		menuButton.buttonRect.width = static_cast<float>(MeasureText(menuButton.text, menuButton.fontSize));
		menuButton.buttonRect.height = static_cast<float>(menuButton.fontSize);
		menuButton.bgColor = GRAY;

		ButtonDraw(menuButton, true);

		DrawText(pauseTitle, GetScreenWidth() / 2 - MeasureText(pauseTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
		DrawText(resumeText, GetScreenWidth() / 2 - MeasureText(resumeText, resumeTextSize) / 2, GetScreenHeight() / 2 - pressKeyWindowLimitSpacing, resumeTextSize, WHITE);
	}

	void GameOverPanelDraw(Button& menuButton, Button& restartButton, bool hasWon)
	{
		const char* title = "Game Over";
		if (hasWon)
			title = "YOU WIN!";

		int titleSize = static_cast<int>(130 * GetScreenScale());

		int buttonsSpacing = 50;

		menuButton.buttonRect.position = { static_cast<float>(GetScreenWidth()) / 2 - MeasureText(menuButton.text, menuButton.fontSize) / 2 , static_cast<float>(GetScreenHeight()) / 2 + buttonsSpacing };
		menuButton.buttonRect.width = static_cast<float>(MeasureText(menuButton.text, menuButton.fontSize));
		menuButton.buttonRect.height = static_cast<float>(menuButton.fontSize);
		menuButton.bgColor = DARKGRAY;

		ButtonDraw(menuButton, true);

		restartButton.buttonRect.position = { static_cast<float>(GetScreenWidth()) / 2 - MeasureText(restartButton.text, restartButton.fontSize) / 2, static_cast<float>(GetScreenHeight()) / 2 - buttonsSpacing };
		restartButton.buttonRect.width = static_cast<float>(MeasureText(restartButton.text, restartButton.fontSize));
		restartButton.buttonRect.height = static_cast<float>(restartButton.fontSize);
		restartButton.bgColor = DARKGRAY;

		ButtonDraw(restartButton, true);

		DrawText(title, GetScreenWidth() / 2 - MeasureText(title, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
	}
}
