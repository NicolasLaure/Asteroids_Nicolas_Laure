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

	Vector2 GetRandomDirection();
	Vector2 GetRandomPosition(float size);
}