#pragma once
#include "GameManagement/Scenes.h"

namespace game
{
	struct SceneManager
	{
		Scenes currentScene;
		Scenes prevScene;
		bool enteredNewScene;

		bool isSinglePlayer;
		bool isPaused = false;
	};
};