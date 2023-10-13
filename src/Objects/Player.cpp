#include "Objects/Player.h"
#include "GameManagement/TexturesManager.h"


namespace asteroids
{
	static const float BASE_SCREEN_WIDTH = 1280.0f;

	void CheckScreenBoundsCollision(Player& player, float screenWidth, float screenHeight);


	void PlayerUpdate(Player& player)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());
		RotatePlayer(player, GetMousePosition());

		player.position = Vector2Add(player.position, Vector2Scale(player.velocity, GetFrameTime()));

		if (IsMouseButtonDown(1))
			player.velocity = Vector2Clamp(Vector2Add(player.velocity, Vector2Scale(player.dir, player.acceleration * (screenWidth / BASE_SCREEN_WIDTH) * GetFrameTime())),
				{ -player.maxVelocity, -player.maxVelocity },
				{ player.maxVelocity, player.maxVelocity });

		CheckScreenBoundsCollision(player, screenWidth, screenHeight);
	}

	void PlayerDraw(Player& player)
	{
		DrawTexturePro(GetTexture(TextureIdentifier::Player), { 0,0,40,40 }, { player.position.x, player.position.y,40,40 }, { 20,20 }, player.angle, WHITE);
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
}