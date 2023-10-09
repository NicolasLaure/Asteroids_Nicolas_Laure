#pragma once
#include "Objects/Player.h"

namespace asteroids
{
	struct GameData
	{
		bool areRulesBeingShown = false;
		bool isPaused = false;
		Player player{};

		bool isGameOver = false;
		bool justRestarted = false;

		int score = 0;

		int lives = 3;
		int maxLives = 3;
		bool hasWon = false;

		int windowUpperLimit = 80;

		int buttonsFontSize = 50;
		Button restartButton = { {0,0}, Scenes::Game, "Restart" };
		Button menuButton = { {0,0}, Scenes::Menu, "Main Menu" };
	};

};