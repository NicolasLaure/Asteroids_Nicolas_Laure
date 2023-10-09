#pragma once
#include "GameManagement/Scenes.h"

namespace asteroids
{
	struct SceneManager
	{
		Scenes currentScene{};
		Scenes prevScene{};
		bool enteredNewScene{};

		bool isSinglePlayer{};
		bool isPaused = false;
	};
};