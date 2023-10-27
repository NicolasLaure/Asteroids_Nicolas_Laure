#include "Objects/UI.h"

#include <string>
using namespace std;

namespace asteroids
{
	void UIDraw(GameData& gd)
	{
		string playerLivesText = "Lives: " + to_string(gd.player.lives);
		DrawText(playerLivesText.c_str(), 0, 0, 40, WHITE);

		string patientHealth = "Patient Health: " + to_string(gd.patient.patientHealth);
		DrawText(patientHealth.c_str(), GetScreenWidth() - MeasureText(patientHealth.c_str(), 40), 0, 40, WHITE);
	}
}
