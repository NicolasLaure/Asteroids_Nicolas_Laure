#pragma once
#include "GameManagement/Scenes.h"

namespace Asteroids
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