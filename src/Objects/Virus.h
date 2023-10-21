#pragma once

#include "GameManagement/Utilities.h"

namespace asteroids
{
	struct Virus
	{
		bool isActive;
	};

	void VirusesStart(Virus viruses[]);
	void VirusesUpdate(Virus viruses[]);
	void VirusesDraw(Virus viruses[]);
	void VirusesColliderDraw(Virus viruses[]);
}