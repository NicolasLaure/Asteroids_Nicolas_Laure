#include "GameManagement/ScreenManager.h"

#include "raylib.h"

namespace asteroids
{
	static float screenScale;

	static const float DEFAULT_WIDTH = 1280;

	void OnScreenSizeChange()
	{
		screenScale = GetScreenWidth() / DEFAULT_WIDTH;
	}

	float GetScreenScale()
	{
		return screenScale;
	}
}