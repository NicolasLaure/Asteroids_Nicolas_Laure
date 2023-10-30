#pragma once
#include "GameManagement/Utilities.h"

namespace asteroids
{
	enum class MusicIdentifier
	{
		MenuMusic,
		GamePlayMusic,
	};
	enum class SoundIdentifier
	{
		ButtonClick,
		ButtonRelease,
		PausePopSound,
		whiteCellExplosion,
		bloodCellExplosion,
		PlayerReceiveDamage,
		PlayerDeath,
		HpUp
	};

	struct AllAudioFiles
	{
		Music menuMusic;
		Music gameplayMusic;

		Sound buttonClick;
		Sound buttonRelease;
		Sound pausePopSound;

		Sound whiteCellExplosion;
		Sound bloodCellExplosion;
		Sound playerTakeDamage;
		Sound playerDeath;
		Sound healthUp;
	};

	void SetSounds();
	Music GetMusic(MusicIdentifier id);
	Sound GetSound(SoundIdentifier id);
}