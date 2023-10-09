#include "Objects/Player.h"
#include "GameManagement/TexturesManager.h"


namespace asteroids
{
	void PlayerUpdate(Player& player)
	{
		RotatePlayer(player, GetMousePosition());

		if (IsMouseButtonDown(1))
			player.position = Vector2Add(player.position, Vector2Scale(player.dir, player.speed * GetFrameTime()));
	}

	void PlayerDraw(Player& player)
	{
		DrawTextureEx(GetTexture(TextureIdentifier::Player), player.position, player.angle, 1, WHITE);
	}

	void RotatePlayer(Player& player, Vector2 mousePos)
	{
		player.angle = static_cast<float>(atan2(player.dir.y, player.dir.x)) * RAD2DEG + 90.0f;
		player.dir = Vector2Normalize(Vector2Subtract(mousePos, { player.position.x + player.size / 2,  player.position.y + player.size / 2 }));
	}

	void ResetPlayer(Player& player)
	{
		player.position = { static_cast<float>(GetScreenWidth()) / 2 - player.size / 2, static_cast<float>(GetScreenHeight()) / 2 - player.size / 2 };
	}
}