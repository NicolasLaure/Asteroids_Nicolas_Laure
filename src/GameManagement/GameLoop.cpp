#include "GameManagement/GameLoop.h"

#include <iostream>
#include "raylib.h"

#include "GameManagement/Menu.h"
#include "GameManagement/SceneManager.h"


using namespace std;
namespace game
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
		SetRandomSeed(time(0));
	}

	void GameLoop()
	{
		do
		{
			sceneManager.enteredNewScene = sceneManager.scene != sceneManager.prevScene;
			sceneManager.prevScene = sceneManager.scene;

			switch (sceneManager.scene)
			{
			case Scenes::GameQuit:
				break;
			case Scenes::Menu:
				if (sceneManager.enteredNewScene)
					MenuStart();

				MenuUpdate(sceneManager.scene);
				MenuDraw();
				break;
			case Scenes::Game:

				break;
			default:
				break;
			}
		} while (sceneManager.scene != Scenes::GameQuit && !WindowShouldClose());
	}
};
