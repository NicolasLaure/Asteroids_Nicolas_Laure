#pragma once

#include "Objects/Player.h"
#include "Objects/BloodCell.h"
#include "Objects/WhiteBloodCells.h"
#include "Objects/Bullet.h"
#include "Objects/Button.h"
#include "GameManagement/Scenes.h"
#include "Objects/Patient.h"

namespace asteroids
{
	struct GameData
	{
		bool areRulesBeingShown = false;
		bool isPaused = false;
		Player player{};

		Patient patient{};

		static const int WHITECELLS_QTY = 80;
		WhiteCell whiteCells[WHITECELLS_QTY] = {};
		
		static const int BLOOD_CELLS_QTY = 80;
		BloodCell bloodCells[BLOOD_CELLS_QTY] = {};

		bool isGameOver = false;
		bool justRestarted = false;

		int score = 0;

		bool hasWon = false;

		int windowUpperLimit = 80;

		int buttonsFontSize = 50;
		Button restartButton = { {0,0}, Scenes::Game, "Restart" };
		Button menuButton = { {0,0}, Scenes::Menu, "Main Menu" };
	};

};