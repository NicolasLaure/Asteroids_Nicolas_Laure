#include "GameManagement/Menu.h"

#include "GameManagement/AudioManager.h"
#include <iostream>

namespace asteroids
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

		PlayMusicStream(GetMusic(MusicIdentifier::MenuMusic));
		float windowLimitSpacing = 20;
		textSize = MeasureTextEx(GetFontDefault(), menuData.itchPageButton.text, static_cast<float>(menuData.itchPageButton.fontSize), menuData.itchPageButton.fontSize * 0.1f);
		menuData.itchPageButton.buttonRect = { {static_cast<float>(GetScreenWidth()) - MeasureText(menuData.credits, menuData.creditsSize) - 20, static_cast<float>(GetScreenHeight()) - menuData.creditsSize - 20}, textSize.y, textSize.x };

		for (int i = 0; i < menuData.buttonsQty; i++)
		{
			textSize = MeasureTextEx(GetFontDefault(), menuData.scenesButtons[i].text, static_cast<float>(menuData.scenesButtons[i].fontSize), menuData.scenesButtons[i].fontSize * 0.1f);
			menuData.scenesButtons[i].buttonRect = { {windowLimitSpacing, static_cast<float>(GetScreenHeight()) / 3 + i * menuData.scenesButtons[i].fontSize * 1.6f}, textSize.y, textSize.x };
		}
	}
	void MenuUpdate(Scenes& scene)
	{
		UpdateMusicStream(GetMusic(MusicIdentifier::MenuMusic));
		if (!menuData.showCreditsScreen)
		{
			ItchPageButtonCollisionCheck(menuData.itchPageButton);
			for (Button& button : menuData.scenesButtons)
			{
				if (button.sceneTo == Scenes::Menu)
					CreditsButtonCollisionCheck(button, menuData.showCreditsScreen);

				ButtonCollisionCheck(button, scene);
			}
		}
		else
		{
			CreditsButtonCollisionCheck(menuData.closeCredits, menuData.showCreditsScreen);
		}
	}

	void MenuDraw()
	{
		BeginDrawing();

		if (!menuData.showCreditsScreen)
		{
			ClearBackground(BLACK);
			DrawText(menuData.title, GetScreenWidth() / 2 - MeasureText(menuData.title, menuData.titleSize) / 2, 20, menuData.titleSize, WHITE);
			DrawText(menuData.credits, GetScreenWidth() - MeasureText(menuData.credits, menuData.creditsSize) - 20, GetScreenHeight() - menuData.creditsSize - 20, menuData.creditsSize, menuData.itchPageButton.currentTextColor);

			for (Button& button : menuData.scenesButtons)
			{
				ButtonDraw(button, false);
			}
		}
		else
		{
			Color panelColor = { 50,50,50,255 };
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), panelColor);

			int creditsSize = 25;
			int creditsHorizontalDisplacement = 20;
			int creditsSpacing = 120;
			const char* santiText = "Player And Asteroids by Santiago Garrido instagram: @tains_art";
			const char* ImpactSoundsText = "Impact Sounds by Kenney https://kenney.nl/assets/impact-sounds";
			const char* InterfaceSoundsText = "Interface Sounds by Kenney https://kenney.nl/assets/interface-sounds";

			DrawText(santiText, creditsHorizontalDisplacement, GetScreenHeight() / 2 - creditsSpacing * 2, creditsSize, WHITE);
			DrawText(ImpactSoundsText, creditsHorizontalDisplacement, GetScreenHeight() / 2 - creditsSpacing, creditsSize, WHITE);
			DrawText(InterfaceSoundsText, creditsHorizontalDisplacement, GetScreenHeight() / 2, creditsSize, WHITE);


			int buttonSpacing = 120;
			menuData.closeCredits.buttonRect.position = { static_cast<float>(GetScreenWidth()) / 2 - static_cast<float>(MeasureText(menuData.closeCredits.text, menuData.closeCredits.fontSize)) / 2, static_cast<float>(GetScreenHeight()) - buttonSpacing };
			menuData.closeCredits.buttonRect.width = static_cast<float>(MeasureText(menuData.closeCredits.text, menuData.closeCredits.fontSize));
			menuData.closeCredits.buttonRect.height = static_cast<float>(menuData.closeCredits.fontSize);
			menuData.closeCredits.bgColor = DARKGRAY;
			ButtonDraw(menuData.closeCredits, true);
		}
		EndDrawing();
	}
};