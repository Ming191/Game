#include<headers/AudioManager.h>

AudioManager:: AudioManager(ButtonManager &p_BM, TextureManager &p_TM, SoundEffect &p_SFX, Music &p_MP)
            : BManager(&p_BM), TManager(&p_TM), SFX(&p_SFX), music(&p_MP)
            {}

void AudioManager::Update()
{
    if (music->GetVolume() != 0)
	{
		BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerPlayTexture);
	}
	if (SFX->GetVolume() != 0)
	{
		BManager->sfxPlayerButton.SetTex(TManager->musicPlayerPlayTexture);
	}
	BManager->handleButton1.SetPos(Vector(30.f+(music->GetVolume()/128.f)*100, BManager->handleButton1.GetPos().GetY()));
	BManager->handleButton2.SetPos(Vector(30.f+(SFX->GetVolume()/128.f)*100, BManager->handleButton2.GetPos().GetY()));
	if (music->IsPlaying() && BManager->handleButton1.GetPos().GetX() <31)
	{
			BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerMuteTexture);
			music->Mute();
	}
	if (SFX->IsPlaying() && BManager->handleButton2.GetPos().GetX() <31)
	{
			BManager->sfxPlayerButton.SetTex(TManager->musicPlayerMuteTexture);
			SFX->Mute();
	}
}

void AudioManager::Init()
{
	music->SetVolume(0.5f);
	SFX->SetVolume(0.1f);
	music->PlayCurrentTrack();
}

void AudioManager::DragAndDropMusic(Vector& mousePos)
{
    BManager->handleButton1.SetPos(Vector(mousePos.GetX()-6, BManager->handleButton1.GetPos().GetY()));
	musicVolume = (BManager->handleButton1.GetPos().GetX()-30) / 100.f;
	music->SetVolume(musicVolume);
}

void AudioManager::DragAndDropSFX(Vector& mousePos)
{
	BManager->handleButton2.SetPos(Vector(mousePos.GetX()-6, BManager->handleButton2.GetPos().GetY()));
	sfxVolume = (BManager->handleButton2.GetPos().GetX()-30) / 100.f;
	SFX->SetVolume(sfxVolume);
}

void AudioManager::MusicPauseAndResume()
{
    if (music->IsPaused())
	{
		BManager->PauseAndResumeMusic.SetTex(TManager->pauseMusicTexture);
		music->Resume();
	}
	else
	{
		BManager->PauseAndResumeMusic.SetTex(TManager->resumeMusicTexture);
		music->Pause();
	}
}

void AudioManager::MusicMuteAndUnMute()
{
    if (music->IsPlaying())
	{
		BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerMuteTexture);
		music->Mute();
	}
	else if(music->IsPlaying() == 0)
	{
		BManager->musicPlayerPlayButton.SetTex(TManager->musicPlayerPlayTexture);
		music->UnMute();
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
		music->PreviousTrack();
	}
	if (commonFunc::isCollide(mousePos, BManager->forwardButton))
	{
		music->NextTrack();
	}
}