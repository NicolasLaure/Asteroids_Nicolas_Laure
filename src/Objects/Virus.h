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

		int phase{ 1 };
		float currentSize{ 20 };
		float normalSize{ 20 };
		float smallSize{ 12.5f };
		float miniSize{ 7.5f };
	};

	void VirusesStart(Virus viruses[], int virusesQty);
	void VirusesUpdate(Virus viruses[], int virusesQty);
	void VirusesDraw(Virus viruses[], int virusesQty);
	void VirusesColliderDraw(Virus viruses[], int virusesQty);
}