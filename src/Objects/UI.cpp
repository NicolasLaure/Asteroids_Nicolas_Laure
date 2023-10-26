#include "Objects/UI.h"
#include <string>
using namespace std;


void UIDraw(int playerLives)
{
	string playerLivesText = "Lives: " + to_string(playerLives);
	DrawText(playerLivesText.c_str(), 0, 0, 40, WHITE);
}
