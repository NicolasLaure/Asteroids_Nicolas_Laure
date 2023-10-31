#pragma once
#include "GameManagement/Utilities.h"

#include "GameManagement/GameData.h"
#include "Objects/Button.h"
namespace asteroids
{
	void HudDraw(GameData& gd);

	void RulesDraw();
	void PausePanelDraw(Button& menuButton);
	void GameOverPanelDraw(Button& menuButton, Button& restartButton);
}

