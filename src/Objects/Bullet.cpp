#include "Objects/Bullet.h"

#include "GameManagement/ScreenManager.h"
#include "GameManagement/TexturesManager.h"

void asteroids::BulletsStart(Bullet bullets[], int bulletsQty)
{
	for (int i = 0; i < bulletsQty; i++)
	{
		bullets[i].isActive = false;
		bullets[i].angle = 0;
		bullets[i].direction = { 0,0 };
		bullets[i].position = { 0,0 };
	}
}

void asteroids::BulletUpdate(Bullet& bullet)
{
	bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.direction, bullet.speed * GetScreenScale() * GetFrameTime()));

	if (bullet.position.x + bullet.size / 2 < 0 || bullet.position.x - bullet.size / 2 > GetScreenWidth() || bullet.position.y + bullet.size / 2 < 0 || bullet.position.y - bullet.size / 2 > GetScreenHeight())
		bullet.isActive = false;
}

static const float BULLET_TEXTURE_SIZE = 80;

void asteroids::BulletDraw(Bullet& bullet)
{
	DrawTexturePro(GetTexture(TextureIdentifier::Bullet), { 0,0, BULLET_TEXTURE_SIZE,BULLET_TEXTURE_SIZE }, { bullet.position.x, bullet.position.y, bullet.size * 2,bullet.size * 2 }, { bullet.size, bullet.size }, bullet.angle, WHITE);
}

void asteroids::BulletColliderDraw(Bullet& bullet)
{
	DrawCircleLines(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.size, GREEN);
}
