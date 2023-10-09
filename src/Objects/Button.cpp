#include "Button.h"

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
			}

			if (IsMouseButtonReleased(0))
			{
				scene = button.sceneTo;
			}
		}
		else
			button.currentTextColor = button.textColor;
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
			}
			//mouse release 
			if (IsMouseButtonReleased(0))
			{
				OpenURL("https://nico-drake.itch.io/");
			}
		}
		else
			button.currentTextColor = button.textColor;
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