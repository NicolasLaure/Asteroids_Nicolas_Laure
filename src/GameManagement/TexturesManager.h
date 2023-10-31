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
	};

	struct AllTextures
	{
		Texture defaultTexture;
		Texture player;
		Texture whiteCell;
		Texture bloodCell;
	};

	void SetTextures();
	Texture GetTexture(TextureIdentifier texture);
}