#include<headers/SFX.h>

Music::Music()
{}

void Music::PlayCurrentTrack() 
{
    if (currIndex >= 0 && currIndex < playList.size()) {
        music = Mix_LoadMUS(playList[currIndex].first.c_str());
        Mix_PlayMusic(music, -1);
        std::cout << "Now playing: " << playList[currIndex].second << std::endl;
    }
}

void Music::NextTrack()
{
    Mix_FreeMusic(music);
    currIndex++;
    if (currIndex >= 9) {
        currIndex = 0; 
    }
    PlayCurrentTrack();
}

void Music::PreviousTrack()
{
    Mix_FreeMusic(music);
    currIndex--;
    if(currIndex < 0)
    {
        currIndex = 8;
    }
    PlayCurrentTrack();
}

void Music::Pause()
{
    isPaused = 1;
    Mix_PauseMusic();
}

void Music::Resume()
{
    isPaused = 0;
    Mix_ResumeMusic();
}

std::string Music::GetTitle()
{
    return playList[currIndex].second;
}

void Music::Mute()
{
    lastVolume = GetVolume();
    if (lastVolume<10)
    {
        lastVolume = 10;
    }
    isPlaying = 0;
    Mix_VolumeMusic(0);
}

void Music::UnMute()
{
    isPlaying = 1;
    SetVolume((float)lastVolume/128);
}

void Music::SetVolume(float delta)
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

int Music::GetVolume()
{
    return Mix_GetMusicVolume(music);
}
Music::~Music()
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