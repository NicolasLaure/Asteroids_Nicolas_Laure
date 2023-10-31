#include "GameManagement/TexturesManager.h"

namespace asteroids
{
	static AllTextures textures;

	void SetTextures()
	{
		textures.defaultTexture = LoadTexture("assets/sprites/DefaultSprite.png");
		textures.player = LoadTexture("assets/sprites/ProtoNave.png");
		textures.whiteCell = LoadTexture("assets/sprites/Globulo_Blanco.png");
		textures.bloodCell = LoadTexture("assets/sprites/Globulo_Rojo.png");
	}
	Texture GetTexture(TextureIdentifier texture)
	{
		switch (texture)
		{
		case asteroids::TextureIdentifier::Player:
			return textures.player;
			break;
		case asteroids::TextureIdentifier::WhiteCell:
			return textures.whiteCell;
			break;
		case asteroids::TextureIdentifier::BloodCell:
			return textures.bloodCell;
			break;
		default:
			return textures.defaultTexture;
			break;
		}
	}
}