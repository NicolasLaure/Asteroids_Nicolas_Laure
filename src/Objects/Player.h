#pragma once
#include "GameManagement/Utilities.h"
#include "Objects/Bullet.h"

namespace asteroids
{

	const float PLAYER_TEXTURE_WIDTH = 28;
	const float PLAYER_TEXTURE_HEIGHT = 30;
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

		float size{ 35 };
		float colliderRadius{};

		static const int BULLETS_QTY = 50;
		Bullet bullets[BULLETS_QTY] = {};
	};

	void PlayerStart(Player& player);

	void PlayerUpdate(Player& player);
	void PlayerDraw(Player& player);
	void PlayerDrawCollider(Player& player);

	void RotatePlayer(Player& player, Vector2 mousePos);
	void ResetPlayer(Player& player);
}