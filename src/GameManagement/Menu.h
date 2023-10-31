#pragma once
#include "Objects/Button.h"
#include "GameManagement/Scenes.h"

namespace asteroids
{
	void MenuScene(bool isNewScene, Scenes& actualScene);

	struct MenuData
	{
		const char* title = "Asteroids";
		int titleSize = 80;
		int titleLimitSpacing = 70;

		const char* credits = "Created By Nico Laure";
		int creditsSize = 30;

		static const int buttonsQty = 3;
		Button scenesButtons[buttonsQty] = {
			{{0,0}, Scenes::Game, "Play"},
			{{0,0}, Scenes::Menu,"Credits"},
			{{0,0}, Scenes::GameQuit,"Exit Game"}

		};

		Button itchPageButton = { {0,0}, Scenes::Menu, credits };

		bool showCreditsScreen = false;
		Button closeCredits = { {0,0}, Scenes::Menu,"Close Credits" };
	};

};