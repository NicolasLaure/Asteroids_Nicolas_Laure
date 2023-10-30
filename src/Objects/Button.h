#pragma once
#include "GameManagement/Utilities.h"
#include "GameManagement/Scenes.h"

namespace asteroids
{
	struct Button
	{
		Rect buttonRect;
		Scenes sceneTo;
		const char* text;
		int fontSize = 70;
		Color textColor = WHITE;
		Color currentTextColor = WHITE;

		float textHeightSpacerMultiplier = 2.25f;
		float textPositionX = 15;

		bool wasPressed{ false };
	};

	void CreditsButtonCollisionCheck(Button& button);
	void ButtonCollisionCheck(Button& button, Scenes& scene);
	void ResetButtonCollisionCheck(Button& button, bool& restartGame);
};