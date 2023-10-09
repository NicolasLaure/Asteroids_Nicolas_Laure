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

		static const int buttonsQty = 2;
		Button scenesButtons[buttonsQty] = {
			{{0,0}, Scenes::Game, "Play"},
			{{0,0}, Scenes::GameQuit,"Exit Game"}
		};

		Button creditsButton = { {0,0}, Scenes::Menu, credits };
	};

};