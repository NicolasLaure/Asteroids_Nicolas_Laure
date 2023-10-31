#include "Button.h"

#include "GameManagement/AudioManager.h"
namespace asteroids
{
	static const Color PRESSED_BUTTON_DARKGRAY = { 20,20,20,160 };

	void ButtonCollisionCheck(Button& button, Scenes& scene)
	{
		Vector2 mousePos = GetMousePosition();

		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = GRAY;
			button.currentBgColor = DARKGRAY;
			if (IsMouseButtonPressed(0))
			{
				button.wasPressed = true;
				if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonClick)))
					PlaySound(GetSound(SoundIdentifier::ButtonClick));
			}

			if (IsMouseButtonDown(0) && button.wasPressed)
			{
				button.currentTextColor = DARKGRAY;
				button.currentBgColor = PRESSED_BUTTON_DARKGRAY;
			}

			if (IsMouseButtonReleased(0))
			{
				if (button.wasPressed)
				{
					if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonRelease)))
						PlaySound(GetSound(SoundIdentifier::ButtonRelease));
					scene = button.sceneTo;
				}
			}
		}
		else
		{
			button.currentBgColor = button.bgColor;
			button.currentTextColor = button.textColor;
			button.wasPressed = false;
		}
	}

	void CreditsButtonCollisionCheck(Button& button)
	{
		Vector2 mousePos = GetMousePosition();

		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = GRAY;

			if (IsMouseButtonPressed(0))
			{
				button.wasPressed = true;
				if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonClick)))
					PlaySound(GetSound(SoundIdentifier::ButtonClick));
			}

			if (IsMouseButtonDown(0) && button.wasPressed)
			{
				button.currentTextColor = DARKGRAY;
				button.currentBgColor = PRESSED_BUTTON_DARKGRAY;
			}

			//mouse release 
			if (IsMouseButtonReleased(0))
			{
				if (button.wasPressed)
				{
					OpenURL("https://nico-drake.itch.io/");
					if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonRelease)))
						PlaySound(GetSound(SoundIdentifier::ButtonRelease));
				}
			}
		}
		else
		{
			button.currentTextColor = button.textColor;
			button.wasPressed = false;
		}
	}

	void ResetButtonCollisionCheck(Button& button, bool& restartGame)
	{
		Vector2 mousePos = GetMousePosition();

		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = GRAY;
			button.currentBgColor = DARKGRAY;
			if (IsMouseButtonPressed(0))
			{
				button.wasPressed = true;
				if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonClick)))
					PlaySound(GetSound(SoundIdentifier::ButtonClick));
			}

			if (IsMouseButtonDown(0) && button.wasPressed)
			{
				button.currentTextColor = DARKGRAY;
				button.currentBgColor = PRESSED_BUTTON_DARKGRAY;
			}

			//mouse release 
			if (IsMouseButtonReleased(0))
			{
				if (button.wasPressed)
				{
					if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonRelease)))
						PlaySound(GetSound(SoundIdentifier::ButtonRelease));
					restartGame = true;
				}
			}
		}
		else
		{
			button.currentBgColor = button.bgColor;
			button.currentTextColor = button.textColor;
			button.wasPressed = false;
		}
	}

	void ButtonDraw(Button& button, bool drawRectangle)
	{
		if (drawRectangle)
			DrawRectangle(static_cast<int>(button.buttonRect.position.x), static_cast<int>(button.buttonRect.position.y), static_cast<int>(button.buttonRect.width), static_cast<int>(button.buttonRect.height), button.currentBgColor);

		DrawText(button.text, static_cast<int>(button.buttonRect.position.x), static_cast<int>(button.buttonRect.position.y), button.fontSize, button.currentTextColor);
	}
};