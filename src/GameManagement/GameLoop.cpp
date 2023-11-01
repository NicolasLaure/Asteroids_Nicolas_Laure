#include "GameManagement/GameLoop.h"

#include <iostream>
#include "raylib.h"

#include "GameManagement/SceneManager.h"
#include "GameManagement/Menu.h"
#include "GameManagement/GamePlay.h"
#include "GameManagement/TexturesManager.h"
#include "GameManagement/AudioManager.h"
#include "GameManagement/ScreenManager.h"

using namespace std;

namespace asteroids
{
	static SceneManager sceneManager;

	void Initialize();
	void GameLoop();

	void RunGame()
	{
		Initialize();
		GameLoop();
		CloseAudioDevice();
		CloseWindow();
	}

	void Initialize()
	{
		InitWindow(1024, 768, "LifeBlood");
		OnScreenSizeChange();
		InitAudioDevice();
		SetExitKey(NULL);
		sceneManager.prevScene = Scenes::GameQuit;
		SetTextures();
		SetSounds();
		SetRandomSeed(static_cast<unsigned int>(time(nullptr)));
	}

	void GameLoop()
	{
		do
		{
			sceneManager.enteredNewScene = sceneManager.currentScene != sceneManager.prevScene;
			sceneManager.prevScene = sceneManager.currentScene;

			switch (sceneManager.currentScene)
			{
			case Scenes::GameQuit:
				break;
			case Scenes::Menu:
				MenuScene(sceneManager.enteredNewScene, sceneManager.currentScene);
				break;
			case Scenes::Game:
				GameScene(sceneManager.enteredNewScene, sceneManager.currentScene);
				break;
			default:
				break;
			}
		} while (sceneManager.currentScene != Scenes::GameQuit && !WindowShouldClose());
	}
};
