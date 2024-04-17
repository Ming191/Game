#pragma once
#include<sfx.h>
#include<button.h>


class AudioManager
{
private:
    SoundEffect* SFX;
    MusicPlayer* musicPlayer;
    ButtonManager* BManager;
    TextureManager* TManager;

    float musicVolume = 0.5f;
    float sfxVolume = 0.1f;
public:
    AudioManager() = default;  
    AudioManager(ButtonManager &p_BM, TextureManager &p_TM, SoundEffect &p_SFX, MusicPlayer &p_MP);
    void Update();
    void Init();
    void DragAndDropMusic(Vector& mousePos);
    void DragAndDropSFX(Vector& mousePos);
    void MusicPauseAndResume();
    void MusicMuteAndUnMute();
    void SFXMuteAndUnMute();

    void HandleClickEvent(Vector& mousePos);
};


