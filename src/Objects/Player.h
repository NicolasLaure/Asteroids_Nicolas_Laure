#pragma once
#include "GameManagement/Utilities.h"
#include "Objects/Bullet.h"

namespace asteroids
{
	
	struct Player
	{
		int lives{ 3 };
		int maxLives{ 3 };
		Vector2 position{};
		Vector2 dir{};
		Vector2 velocity{};

		float maxVelocity{ 1500.0f };
		float friction{ 20.0f };

		bool isImmortal{ false };
		float immortalityDuration{ 1.0f };
		
		bool isThrusting{ false };

		float acceleration{ 500.0f };
		float deceleration{ 100.0f };
		float angle{};

		float size{};
		float colliderRadius{};

		float shootCoolDown{ 0.2f };
		
		bool canShoot{true};
		static const int BULLETS_QTY = 50;
		Bullet bullets[BULLETS_QTY] = {};
	};

	void PlayerStart(Player& player);

	void PlayerUpdate(Player& player);
	void PlayerDraw(Player& player);
	void PlayerDrawCollider(Player& player);

	void RotatePlayer(Player& player, Vector2 mousePos);
	void ResetPlayer(Player& player);

	void TakeDamage(Player& player, bool& isGameOver);
	void PlayerHealthUp(Player& player);

}