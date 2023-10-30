#include "Button.h"

#include "GameManagement/AudioManager.h"
namespace asteroids
{

	void ButtonCollisionCheck(Button& button, Scenes& scene)
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
				button.currentTextColor = DARKGRAY;
				if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonClick)))
					PlaySound(GetSound(SoundIdentifier::ButtonClick));
				button.wasPressed = true;
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

			//mouse down
			if (IsMouseButtonPressed(0))
			{
				button.currentTextColor = DARKGRAY;
				if (!IsSoundPlaying(GetSound(SoundIdentifier::ButtonClick)))
					PlaySound(GetSound(SoundIdentifier::ButtonClick));
				button.wasPressed = true;
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

			//mouse down
			if (IsMouseButtonPressed(0))
			{
				button.currentTextColor = DARKGRAY;
			}
			//mouse release 
			if (IsMouseButtonReleased(0))
			{
				restartGame = true;
			}
		}
		else
			button.currentTextColor = button.textColor;
	}
};