#include "Objects/Bullet.h"

#include "GameManagement/ScreenManager.h"

void asteroids::BulletsStart(Bullet bullets[], int bulletsQty)
{
	for (int i = 0; i < bulletsQty; i++)
	{
		bullets[i].isActive = false;
		bullets[i].angle = 0;
		bullets[i].direction = {0,0};
		bullets[i].position = {0,0};
	}
}

void asteroids::BulletUpdate(Bullet& bullet)
{
	bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.direction, bullet.speed * GetScreenScale() * GetFrameTime()));

	if (bullet.position.x + bullet.size / 2 < 0 || bullet.position.x - bullet.size / 2 > GetScreenWidth() || bullet.position.y + bullet.size / 2 < 0 || bullet.position.y - bullet.size / 2 > GetScreenHeight())
		bullet.isActive = false;
}

void asteroids::BulletDraw(Bullet& bullet)
{
	DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.size, DARKGREEN);
		//DrawTexturePro(GetTexture(TextureIdentifier::Player), { 0,0, PLAYER_TEXTURE_WIDTH,PLAYER_TEXTURE_HEIGHT }, { player.position.x, player.position.y,player.size,player.size }, { player.size / 2,player.size / 2 }, player.angle, WHITE);
}

void asteroids::BulletColliderDraw(Bullet& bullet)
{
	DrawCircleLines(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.size, GREEN);
}
