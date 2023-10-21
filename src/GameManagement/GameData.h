#pragma once
#include "Objects/Player.h"
#include "Objects/BloodCell.h"
#include "Objects/Virus.h"
#include "Objects/BloodCell.h"
#include "Objects/Bullet.h"
namespace asteroids
{
	struct GameData
	{
		bool areRulesBeingShown = false;
		bool isPaused = false;
		Player player{};

		static const int VIRUSES_QTY = 80;
		Virus viruses[VIRUSES_QTY] = {};

		

		static const int BLOOD_CELLS_QTY = 40;
		BloodCell bloodCells[BLOOD_CELLS_QTY] = {};

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