#pragma once
#include "GameManagement/Utilities.h"

namespace asteroids
{
	enum class TextureIdentifier
	{
		Default,
		Player,
		WhiteCell,
		BloodCell,
		Bullet
	};

	struct AllTextures
	{
		Texture defaultTexture;
		Texture player;
		Texture whiteCell;
		Texture bloodCell;
		Texture bullet;
	};

	void SetTextures();
	Texture GetTexture(TextureIdentifier texture);
}