#include "GameManagement/TexturesManager.h"

namespace asteroids
{
	static AllTextures textures;

	void SetTextures()
	{
		textures.defaultTexture = LoadTexture("assets/sprites/DefaultSprite.png");
		textures.player = LoadTexture("assets/sprites/Nanobot.png");
		textures.whiteCell = LoadTexture("assets/sprites/Globulo_Blanco.png");
		textures.bloodCell = LoadTexture("assets/sprites/Globulo_Rojo.png");
		textures.bullet = LoadTexture("assets/sprites/bullet.png");
		textures.healthUp = LoadTexture("assets/sprites/HealthUp.png");
	}
	Texture GetTexture(TextureIdentifier texture)
	{
		switch (texture)
		{
		case TextureIdentifier::Player:
			return textures.player;
			break;
		case TextureIdentifier::WhiteCell:
			return textures.whiteCell;
			break;
		case TextureIdentifier::BloodCell:
			return textures.bloodCell;
			break;
		case TextureIdentifier::Bullet:
			return textures.bullet;
			break;
		case TextureIdentifier::HealthUp:
			return textures.healthUp;
			break;
		default:
			return textures.defaultTexture;
			break;
		}
	}
}