#pragma once
#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct Player
	{
		Vector2 position{};
		Vector2 dir{};
		Vector2 velocity{};

		float maxVelocity{1500.0f};
		float friction{20.0f};

		float healthPoints{ 20.0f };
		float acceleration{ 500.0f };
		float angle{};

		int size{ 40 };
	};


	void PlayerUpdate(Player& player);
	void PlayerDraw(Player& player);

	void RotatePlayer(Player& player, Vector2 mousePos);
	void ResetPlayer(Player& player);
}