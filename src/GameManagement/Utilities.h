#pragma once
#include "raylib.h"
#include "raymath.h"

namespace asteroids
{
	struct Rect
	{
		Vector2 position{};
		float height{};
		float width{};
	};
}