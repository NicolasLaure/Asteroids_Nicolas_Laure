#include "PowerUp.h"

#include "GameManagement/TexturesManager.h"
#include "GameManagement/AudioManager.h"

namespace asteroids
{
	void PowerUpStart(PowerUp& powerUp, Vector2 position)
	{
		powerUp.isActive = true;
		powerUp.position = position;
	}
	void PowerUpReset(PowerUp& powerUp)
	{
		powerUp.isActive = false;
	}

	static const float POWERUP_TEXTURE_SIZE = 128;
	void PowerUpDraw(PowerUp& powerUp)
	{
		if (powerUp.isActive)
			DrawTexturePro(GetTexture(TextureIdentifier::HealthUp), { 0,0, POWERUP_TEXTURE_SIZE ,POWERUP_TEXTURE_SIZE }, { powerUp.position.x, powerUp.position.y,powerUp.size * 2,powerUp.size * 2 }, { powerUp.size,powerUp.size }, 0, WHITE);
	}
	void PowerUpDrawCollider(PowerUp& powerUp)
	{
		if (powerUp.isActive)
			DrawCircleLines(static_cast<int>(powerUp.position.x), static_cast<int>(powerUp.position.y), powerUp.size, GREEN);
	}
	void PowerUpDestroy(PowerUp& powerUp)
	{
		PlaySound(GetSound(SoundIdentifier::HpUp));
		powerUp.isActive = false;
	}
}