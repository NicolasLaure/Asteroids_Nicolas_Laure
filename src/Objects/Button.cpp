#include "Button.h"

namespace game
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
			if (IsMouseButtonDown(0))
			{
				button.currentTextColor = DARKGRAY;
			}

			if (IsMouseButtonUp(0))
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
			if (IsMouseButtonDown(0))
			{
				button.currentTextColor = DARKGRAY;
			}
			//mouse release 
			if (IsMouseButtonUp(0))
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
			if (IsMouseButtonDown(0))
			{
				button.currentTextColor = DARKGRAY;
			}
			//mouse release 
			if (IsMouseButtonUp(0))
			{
				restartGame = true;
			}
		}
		else
			button.currentTextColor = button.textColor;
	}
};