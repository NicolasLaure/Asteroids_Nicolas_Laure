#include "GameManagement/AudioManager.h"

namespace asteroids
{
	static AllAudioFiles audioFiles;

	static float volume = 0.3f;
	void SetSounds()
	{
		SetMasterVolume(volume);
		audioFiles.menuMusic = LoadMusicStream("assets/audio/music/Menu.wav");
		audioFiles.gameplayMusic = LoadMusicStream("assets/audio/music/Gameplay.wav");

		audioFiles.buttonClick = LoadSound("assets/audio/ui/click_001.ogg");
		audioFiles.buttonRelease = LoadSound("assets/audio/ui/click_003.ogg");
		audioFiles.pausePopSound = LoadSound("assets/audio/ui/drop_001.ogg");

		audioFiles.bloodCellExplosion = LoadSound("assets/audio/sfx/footstep_concrete_002.ogg");
		audioFiles.whiteCellExplosion = LoadSound("assets/audio/sfx/footstep_grass_003.ogg");
		audioFiles.playerTakeDamage = LoadSound("assets/audio/sfx/impactBell_heavy_004.ogg");
		audioFiles.playerDeath = LoadSound("assets/audio/sfx/error_003.ogg");
		audioFiles.playerShoot = LoadSound("assets/audio/sfx/impactMetal_heavy_003.ogg");
		audioFiles.healthUp = LoadSound("assets/audio/sfx/impactMining_001.ogg");
	}
	Music GetMusic(MusicIdentifier id)
	{
		if (id == MusicIdentifier::MenuMusic)
			return audioFiles.menuMusic;
		else
			return audioFiles.gameplayMusic;
	}
	Sound GetSound(SoundIdentifier id)
	{
		switch (id)
		{
		case SoundIdentifier::ButtonClick:
			return audioFiles.buttonClick;
			break;
		case SoundIdentifier::ButtonRelease:
			return audioFiles.buttonRelease;
			break;
		case SoundIdentifier::PausePopSound:
			return audioFiles.pausePopSound;
			break;
		case SoundIdentifier::whiteCellExplosion:
			return audioFiles.whiteCellExplosion;
			break;
		case SoundIdentifier::bloodCellExplosion:
			return audioFiles.bloodCellExplosion;
			break;
		case SoundIdentifier::PlayerReceiveDamage:
			return audioFiles.playerTakeDamage;
			break;
		case SoundIdentifier::PlayerDeath:
			return audioFiles.playerDeath;
			break;
		case SoundIdentifier::PlayerShoot:
			return audioFiles.playerShoot;
			break;
		case SoundIdentifier::HpUp:
			return audioFiles.healthUp;
			break;
		default:
			return audioFiles.buttonClick;
			break;
		}
	}
}