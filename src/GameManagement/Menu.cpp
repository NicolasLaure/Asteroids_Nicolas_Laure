#include "GameManagement/Menu.h"

#include <iostream>

namespace game
{
	static MenuData menuData;

	void MenuStart();
	void MenuUpdate(Scenes& scene);
	void MenuDraw();

	void MenuScene(bool isNewScene, Scenes& actualScene)
	{
		if (isNewScene)
			MenuStart();

		MenuUpdate(actualScene);
		MenuDraw();
	}
	void MenuStart()
	{
		Vector2 textSize = { 0,0 };

		float windowLimitSpacing = 20;
		textSize = MeasureTextEx(GetFontDefault(), menuData.creditsButton.text, menuData.creditsButton.fontSize, menuData.creditsButton.fontSize * 0.1f);
		menuData.creditsButton.buttonRect = { {static_cast<float>(GetScreenWidth()) - MeasureText(menuData.credits, menuData.creditsSize) - 20, static_cast<float>(GetScreenHeight()) - menuData.creditsSize - 20}, textSize.y, textSize.x };

		for (int i = 0; i < menuData.buttonsQty; i++)
		{
			textSize = MeasureTextEx(GetFontDefault(), menuData.scenesButtons[i].text, menuData.scenesButtons[i].fontSize, menuData.scenesButtons[i].fontSize * 0.1f);
			menuData.scenesButtons[i].buttonRect = { {windowLimitSpacing, static_cast<float>(GetScreenHeight()) / 3 + i * menuData.scenesButtons[i].fontSize * 1.6f}, textSize.y, textSize.x };
		}
	}
	void MenuUpdate(Scenes& scene)
	{
		CreditsButtonCollisionCheck(menuData.creditsButton);
		for (Button& button : menuData.scenesButtons)
		{
			ButtonCollisionCheck(button, scene);
		}
	}

	void MenuDraw()
	{
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText(menuData.title, GetScreenWidth() / 2 - MeasureText(menuData.title, menuData.titleSize) / 2, 20, menuData.titleSize, WHITE);
		DrawText(menuData.credits, GetScreenWidth() - MeasureText(menuData.credits, menuData.creditsSize) - 20, GetScreenHeight() - menuData.creditsSize - 20, menuData.creditsSize, WHITE);

		for (Button& button : menuData.scenesButtons)
		{
			//DrawRectangle(button.buttonRect.position.x, button.buttonRect.position.y, button.buttonRect.width, button.buttonRect.height, BLACK);
			DrawText(button.text, button.buttonRect.position.x, button.buttonRect.position.y, button.fontSize, button.currentTextColor);
		}
		EndDrawing();
	}
};