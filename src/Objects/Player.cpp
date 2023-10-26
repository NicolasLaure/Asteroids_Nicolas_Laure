#include "Objects/Player.h"

#include "GameManagement/TexturesManager.h"
#include "GameManagement/ScreenManager.h"

namespace asteroids
{
	static const float BASE_SCREEN_WIDTH = 1280.0f;

	void CheckScreenBoundsCollision(Player& player, float screenWidth, float screenHeight);
	void Shoot(Player& player);


	void PlayerStart(Player& player)
	{
		player.size *= GetScreenScale();
		player.colliderRadius = player.size / 2 * 0.75f;
	}

	void PlayerUpdate(Player& player)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());
		RotatePlayer(player, GetMousePosition());

		player.position = Vector2Add(player.position, Vector2Scale(player.velocity, GetScreenScale() * GetFrameTime()));

		if (IsMouseButtonDown(1))
			player.velocity = Vector2Clamp(Vector2Add(player.velocity, Vector2Scale(player.dir, player.acceleration * GetFrameTime())),
				{ -player.maxVelocity, -player.maxVelocity },
				{ player.maxVelocity, player.maxVelocity });
		else
		{
			if (player.velocity.x < 0)
				player.velocity.x += player.deceleration * GetFrameTime();
			else if(player.velocity.x > 0)
				player.velocity.x -= player.deceleration * GetFrameTime();

			if (player.velocity.y < 0)
				player.velocity.y += player.deceleration * GetFrameTime();
			else if (player.velocity.y > 0)
				player.velocity.y -= player.deceleration * GetFrameTime();
		}

		CheckScreenBoundsCollision(player, screenWidth, screenHeight);

		if (IsMouseButtonPressed(0))
		{
			Shoot(player);
		}
	}

	void PlayerDraw(Player& player)
	{
		DrawTexturePro(GetTexture(TextureIdentifier::Player), { 0,0, PLAYER_TEXTURE_WIDTH,PLAYER_TEXTURE_HEIGHT }, { player.position.x, player.position.y,player.size,player.size }, { player.size / 2,player.size / 2 }, player.angle, WHITE);
	}

	void PlayerDrawCollider(Player& player)
	{
		DrawCircleLines(static_cast<int>(player.position.x), static_cast<int>(player.position.y), player.colliderRadius, GREEN);
	}

	void RotatePlayer(Player& player, Vector2 mousePos)
	{
		player.angle = static_cast<float>(atan2(player.dir.y, player.dir.x)) * RAD2DEG + 90.0f;
		player.dir = Vector2Normalize(Vector2Subtract(mousePos, { player.position.x,  player.position.y }));
	}

	void ResetPlayer(Player& player)
	{
		player.position = { static_cast<float>(GetScreenWidth()) / 2 - player.size / 2, static_cast<float>(GetScreenHeight()) / 2 - player.size / 2 };
	}

	void CheckScreenBoundsCollision(Player& player, float screenWidth, float screenHeight)
	{
		if (player.position.x + player.velocity.x * GetFrameTime() > screenWidth)
		{
			player.position.x = 0;
			if (player.velocity.y > 0)
			{
				if (player.position.y > screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
			else if (player.velocity.y < 0)
			{
				if (player.position.y < screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
		}
		else if (player.position.x + player.velocity.x * GetFrameTime() < 0)
		{
			player.position.x = screenWidth;
			if (player.velocity.y > 0)
			{
				if (player.position.y > screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
			else if (player.velocity.y < 0)
			{
				if (player.position.y < screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
		}

		if (player.position.y + player.velocity.y * GetFrameTime() > screenHeight)
		{
			player.position.y = 0;
			if (player.velocity.x > 0)
			{
				if (player.position.x > screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
			else if (player.velocity.x < 0)
			{
				if (player.position.x < screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
		}
		else if (player.position.y + player.velocity.y * GetFrameTime() < 0)
		{
			player.position.y = screenHeight;
			if (player.velocity.x > 0)
			{
				if (player.position.x > screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
			else if (player.velocity.x < 0)
			{
				if (player.position.x < screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
		}
	}

	void Shoot(Player& player)
	{
		for (int i = 0; i < player.BULLETS_QTY; i++)
		{
			if (!player.bullets[i].isActive)
			{
				player.bullets[i].isActive = true;
				player.bullets[i].position = player.position;
				player.bullets[i].direction = player.dir;
				player.bullets[i].angle = player.angle;
				break;
			}
		}
	}

	void TakeDamage(Player& player)
	{
		player.lives--;
	}

}