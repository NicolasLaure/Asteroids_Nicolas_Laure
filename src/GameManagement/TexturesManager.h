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
		Bullet,
		HealthUp
	};

	struct AllTextures
	{
		Texture defaultTexture;
		Texture player;
		Texture whiteCell;
		Texture bloodCell;
		Texture bullet;
		Texture healthUp;
	};

	void SetTextures();
	Texture GetTexture(TextureIdentifier texture);
}