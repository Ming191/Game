#include<headers/SFX.h>

MusicPlayer::MusicPlayer()
{}

void MusicPlayer::PlayCurrentTrack() 
{
    if (currIndex >= 0 && currIndex < playList.size()) {
        music = Mix_LoadMUS(playList[currIndex].first.c_str());
        Mix_PlayMusic(music, -1);
        std::cout << "Now playing: " << playList[currIndex].second << std::endl;
    }
}

void MusicPlayer::NextTrack()
{
    Mix_FreeMusic(music);
    currIndex++;
    if (currIndex >= 9) {
        currIndex = 0; 
    }
    PlayCurrentTrack();
}

void MusicPlayer::PreviousTrack()
{
    Mix_FreeMusic(music);
    currIndex--;
    if(currIndex < 0)
    {
        currIndex = 8;
    }
    PlayCurrentTrack();
}

void MusicPlayer::Pause()
{
    isPaused = 1;
    Mix_PauseMusic();
}

void MusicPlayer::Resume()
{
    isPaused = 0;
    Mix_ResumeMusic();
}

std::string MusicPlayer::GetTitle()
{
    return playList[currIndex].second;
}

void MusicPlayer::Mute()
{
    lastVolume = GetVolume();
    if (lastVolume<10)
    {
        lastVolume = 10;
    }
    isPlaying = 0;
    Mix_VolumeMusic(0);
}

void MusicPlayer::UnMute()
{
    isPlaying = 1;
    SetVolume((float)lastVolume/128);
}

void MusicPlayer::SetVolume(float delta)
{
    Mix_VolumeMusic(delta*MIX_MAX_VOLUME);
    if (delta != 0)
    {
        isPlaying = 1;
    } else
    {
        isPlaying = 0;
    }
}

int MusicPlayer::GetVolume()
{
    return Mix_GetMusicVolume(music);
}
MusicPlayer::~MusicPlayer()
{
    Mix_FreeMusic(music);
}



SoundEffect::SoundEffect()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    sounds[JUMP] = Mix_LoadWAV("res/sfx/audio_wing.wav");
    sounds[COIN_HIT] = Mix_LoadWAV("res/sfx/audio_point.wav");
    sounds[PIPE_HIT] = Mix_LoadWAV("res/sfx/audio_die.wav");
}

void SoundEffect::Play(int index)
{
     if (Mix_PlayChannel(-1, sounds[index], 0) == -1) {
        std::cerr << "Failed to play sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void SoundEffect::Mute()
{
    lastVolume = GetVolume();
    if (lastVolume<10)
    {
        lastVolume = 10;
    }
    // std::cout << lastVolume << std::endl;
    isPlaying = 0;
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_VolumeChunk(sounds[i], 0);
    }
}

void SoundEffect::UnMute()
{
    isPlaying = 1;
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_VolumeChunk(sounds[i], lastVolume);
    }
}

void SoundEffect::SetVolume(float delta)
{
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_VolumeChunk(sounds[i], MIX_MAX_VOLUME*delta);
    }

    if (delta != 0)
    {
        isPlaying = 1;
    } else
    {
        isPlaying = 0;
    }
}

int SoundEffect::GetVolume()
{
    return Mix_VolumeChunk(sounds[0], -1);
}

SoundEffect::~SoundEffect()
{
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_FreeChunk(sounds[i]);
    }
}



AudioManager:: AudioManager(ButtonManager &p_BM, TextureManager &p_TM, SoundEffect &p_SFX, MusicPlayer &p_MP)
            : BManager(&p_BM), TManager(&p_TM), SFX(&p_SFX), musicPlayer(&p_MP)
            {}

void AudioManager::Update()
{
    	if (musicPlayer->GetVolume() != 0)
		{
			BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerPlayTexture);
		}
		if (SFX->GetVolume() != 0)
		{
			BManager->sfxPlayerButton.SetTex(TManager->musicPlayerPlayTexture);
		}
		BManager->handleButton1.SetPos(Vector(30.f+(musicPlayer->GetVolume()/128.f)*100, BManager->handleButton1.GetPos().GetY()));
		BManager->handleButton2.SetPos(Vector(30.f+(SFX->GetVolume()/128.f)*100, BManager->handleButton2.GetPos().GetY()));

		if (musicPlayer->IsPlaying() && BManager->handleButton1.GetPos().GetX() <31)
		{
				BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerMuteTexture);
				musicPlayer->Mute();
		}
		if (SFX->IsPlaying() && BManager->handleButton2.GetPos().GetX() <31)
		{
				BManager->sfxPlayerButton.SetTex(TManager->musicPlayerMuteTexture);
				SFX->Mute();
		}
}

void AudioManager::Init()
{
	musicPlayer->SetVolume(0.5f);
	SFX->SetVolume(0.1f);
	musicPlayer->PlayCurrentTrack();
}

void AudioManager::DragAndDropMusic(Vector& mousePos)
{
    BManager->handleButton1.SetPos(Vector(mousePos.GetX()-6, BManager->handleButton1.GetPos().GetY()));
	musicVolume = (BManager->handleButton1.GetPos().GetX()-30) / 100.f;
	musicPlayer->SetVolume(musicVolume);
}

void AudioManager::DragAndDropSFX(Vector& mousePos)
{
	BManager->handleButton2.SetPos(Vector(mousePos.GetX()-6, BManager->handleButton2.GetPos().GetY()));
	sfxVolume = (BManager->handleButton2.GetPos().GetX()-30) / 100.f;
	SFX->SetVolume(sfxVolume);
}

void AudioManager::MusicPauseAndResume()
{
    if (musicPlayer->IsPaused())
	{
		BManager->PauseAndResumeMusic.SetTex(TManager->pauseMusicTexture);
		musicPlayer->Resume();
	}
	else
	{
		BManager->PauseAndResumeMusic.SetTex(TManager->resumeMusicTexture);
		musicPlayer->Pause();
	}
}

void AudioManager::MusicMuteAndUnMute()
{
    if (musicPlayer->IsPlaying())
	{
		BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerMuteTexture);
		musicPlayer->Mute();
	}
	else if(musicPlayer->IsPlaying() == 0)
	{
		BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerPlayTexture);
		musicPlayer->UnMute();
	}
}

void AudioManager::SFXMuteAndUnMute()
{
    if(SFX->IsPlaying())
	{
		BManager->sfxPlayerButton.SetTex(TManager->musicPlayerMuteTexture);
		SFX->Mute();
	}
	else
	{
		BManager->sfxPlayerButton.SetTex(TManager->musicPlayerPlayTexture);
		SFX->UnMute();
	}
}

void AudioManager::HandleClickEvent(Vector& mousePos)
{
if(commonFunc::isCollide(mousePos, BManager->musicPlayerPlayButton))
	{
		MusicMuteAndUnMute();
	}
	if (commonFunc::isCollide(mousePos, BManager->sfxPlayerButton))
	{
		SFXMuteAndUnMute();
	}
	if (commonFunc::isCollide(mousePos, BManager->PauseAndResumeMusic))
	{
		MusicPauseAndResume();
	}
	if (commonFunc::isCollide(mousePos, BManager->backwardButton))
	{
		musicPlayer->PreviousTrack();
	}
	if (commonFunc::isCollide(mousePos, BManager->forwardButton))
	{
		musicPlayer->NextTrack();
	}
}