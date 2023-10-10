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
		DrawTexturePro(GetTexture(TextureIdentifier::Player), { 0,0,40,40 }, { player.position.x, player.position.y,40,40 }, {20,20}, player.angle, WHITE);
	}

	void RotatePlayer(Player& player, Vector2 mousePos)
	{
		player.angle = static_cast<float>(atan2(player.dir.y, player.dir.x)) * RAD2DEG + 90.0f;
		player.dir = Vector2Normalize(Vector2Subtract(mousePos, { player.position.x,  player.position.y}));
	}

	void ResetPlayer(Player& player)
	{
		player.position = { static_cast<float>(GetScreenWidth()) / 2 - player.size / 2, static_cast<float>(GetScreenHeight()) / 2 - player.size / 2 };
	}
}