#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct Virus
	{
		bool isActive;

		Vector2 position;
		Vector2 dir;
		float speed{ 100 };

		float size{ 20 };
	};

	void VirusesStart(Virus viruses[], int virusesQty);
	void VirusesUpdate(Virus viruses[], int virusesQty);
	void VirusesDraw(Virus viruses[], int virusesQty);
	void VirusesColliderDraw(Virus viruses[], int virusesQty);
}