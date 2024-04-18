#include<headers/AudioManager.h>

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