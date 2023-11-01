#include "Objects/Player.h"

#include "GameManagement/TexturesManager.h"
#include "GameManagement/ScreenManager.h"
#include "GameManagement/AudioManager.h"

namespace asteroids
{
	static float immortalityTimer = 0;
	static float shootTimer = 0;

	static const float PLAYER_SPRITE_WIDTH = 88;
	static const float PLAYER_TEXTURE_WIDTH = 352;
	static const float PLAYER_TEXTURE_HEIGHT = 112;

	static int frameCount = 1;

	bool nextFrameReady = false;
	float frameCoolDown = 0.1f;
	float frameTimer = 0;

	void CheckScreenBoundsCollision(Player& player, float screenWidth, float screenHeight);
	void Shoot(Player& player);

	void PlayerStart(Player& player)
	{
		player.size = 50;
		player.size *= GetScreenScale();
		player.colliderRadius = player.size / 2 * 0.7f;
		player.isImmortal = false;
	}

	void PlayerUpdate(Player& player)
	{
		float screenWidth = static_cast<float>(GetScreenWidth());
		float screenHeight = static_cast<float>(GetScreenHeight());
		RotatePlayer(player, GetMousePosition());

		player.position = Vector2Add(player.position, Vector2Scale(player.velocity, GetScreenScale() * GetFrameTime()));

		if (IsMouseButtonDown(1))
		{
			player.velocity = Vector2Clamp(Vector2Add(player.velocity, Vector2Scale(player.dir, player.acceleration * GetFrameTime())),
				{ -player.maxVelocity, -player.maxVelocity },
				{ player.maxVelocity, player.maxVelocity });

			player.isThrusting = true;
		}
		else
		{
			player.velocity = Vector2Add(player.velocity, Vector2Scale(Vector2Normalize(player.velocity), -1 * player.deceleration * GetFrameTime()));
			player.isThrusting = false;
		}

		CheckScreenBoundsCollision(player, screenWidth, screenHeight);

		if (IsMouseButtonPressed(0) && player.canShoot)
			Shoot(player);

		if (!player.canShoot)
			shootTimer += GetFrameTime();

		if (shootTimer >= player.shootCoolDown)
		{
			player.canShoot = true;
			shootTimer = 0;
		}

		if (player.isImmortal)
			immortalityTimer += GetFrameTime();

		if (immortalityTimer >= player.immortalityDuration)
		{
			player.isImmortal = false;
			immortalityTimer = 0;
		}

		if (!nextFrameReady)
			frameTimer += GetFrameTime();

		if (frameTimer > frameCoolDown)
		{
			nextFrameReady = true;
			frameTimer = 0;
		}
	}

	void PlayerDraw(Player& player)
	{
		if (player.isImmortal)
		{
			if (static_cast<int>((immortalityTimer * 10)) % 2 == 0)
				return;
		}

		float ratio = PLAYER_TEXTURE_HEIGHT / PLAYER_SPRITE_WIDTH;
		if (!player.isThrusting)
		{
			DrawTexturePro(GetTexture(TextureIdentifier::Player), { 0,0, PLAYER_SPRITE_WIDTH,PLAYER_TEXTURE_HEIGHT },
				{ player.position.x, player.position.y, player.size, player.size * ratio },
				{ player.size / 2,player.size / 2.0f }, player.angle, WHITE);
		}
		else
		{
			DrawTexturePro(GetTexture(TextureIdentifier::Player), { PLAYER_SPRITE_WIDTH * frameCount,0, PLAYER_SPRITE_WIDTH,PLAYER_TEXTURE_HEIGHT },
				{ player.position.x, player.position.y, player.size, player.size * ratio },
				{ player.size / 2,player.size / 2.0f }, player.angle, WHITE);

			if (nextFrameReady)
			{
				frameCount++;
				if (frameCount > 3)
					frameCount = 1;
				nextFrameReady = false;
			}
		}
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
		player.lives = player.maxLives;
		player.velocity = { 0,0 };
	}

	void TakeDamage(Player& player, bool& isGameOver)
	{
		player.lives--;
		if (player.lives <= 0)
		{
			PlaySound(GetSound(SoundIdentifier::PlayerDeath));
			isGameOver = true;
		}

		PlaySound(GetSound(SoundIdentifier::PlayerReceiveDamage));

		player.isImmortal = true;
	}

	void PlayerHealthUp(Player& player)
	{
		player.lives++;
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
				PlaySound(GetSound(SoundIdentifier::PlayerShoot));

				player.canShoot = false;
				break;
			}
		}
	}

}