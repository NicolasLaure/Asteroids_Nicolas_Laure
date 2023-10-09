#include "GameManagement/TexturesManager.h"

namespace asteroids
{
	static AllTextures textures;

	void SetTextures()
	{
		textures.player = LoadTexture("assets/sprites/ProtoNave.png");
		textures.defaultTexture = LoadTexture("assets/sprites/DefaultSprite.png");
	}
	Texture GetTexture(TextureIdentifier texture)
	{
		switch (texture)
		{
		case asteroids::TextureIdentifier::Player:
			return textures.player;
			break;
		default:
			return textures.defaultTexture;
			break;
		}
	}
}