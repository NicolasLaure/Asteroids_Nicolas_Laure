#pragma once
#include "GameManagement/Utilities.h"

namespace asteroids
{
	enum class TextureIdentifier
	{
		Default,
		Player
	};

	struct AllTextures
	{
		Texture defaultTexture;
		Texture player;
	};

	void SetTextures();
	Texture GetTexture(TextureIdentifier texture);
}