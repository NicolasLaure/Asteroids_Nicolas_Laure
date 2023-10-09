#pragma once
#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct Player
	{
		Vector2 position{};
		Vector2 dir{};

		float healthPoints{ 20 };
		float speed{ 500 };
		float angle{};

		int size{ 40 };
	};


	void PlayerUpdate(Player& player);
	void PlayerDraw(Player& player);

	void RotatePlayer(Player& player, Vector2 mousePos);
	void ResetPlayer(Player& player);
}