#include "GameManagement/GameLoop.h"

#include <iostream>
#include "raylib.h"

#include "GameManagement/Menu.h"
#include "GameManagement/SceneManager.h"


using namespace std;
namespace Asteroids
{
	static SceneManager sceneManager;

	void Initialize();
	void GameLoop();

	void RunGame()
	{
		Initialize();
		GameLoop();
		CloseWindow();
	}

	void Initialize()
	{
		InitWindow(1280, 720, "Asteroids");
		SetExitKey(NULL);
		sceneManager.prevScene = Scenes::GameQuit;
		SetRandomSeed(time(0));
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

				break;
			default:
				break;
			}
		} while (sceneManager.currentScene != Scenes::GameQuit && !WindowShouldClose());
	}
};
