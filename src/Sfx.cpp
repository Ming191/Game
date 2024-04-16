#include<headers/sfx.h>

MusicPlayer::MusicPlayer()
{
    Mix_VolumeMusic(MIX_MAX_VOLUME*0.5f);
}

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
std::string MusicPlayer::GetTitle()
{
    return playList[currIndex].second;
}


void MusicPlayer::Mute()
{
    SwitchState();
    Mix_VolumeMusic(0);
}

void MusicPlayer::UnMute()
{
    SwitchState();
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void MusicPlayer::SetVolume(float delta)
{
    Mix_VolumeMusic(delta*MIX_MAX_VOLUME);
}

MusicPlayer::~MusicPlayer()
{
    Mix_FreeMusic(music);
}

SoundEffect::SoundEffect()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    sounds[JUMP] = Mix_LoadWAV("res/sfx/audio_wing.wav");
    sounds[COIN_HIT] = Mix_LoadWAV("res/sfx/audio_point.wav");
    sounds[PIPE_HIT] = Mix_LoadWAV("res/sfx/audio_die.wav");
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_VolumeChunk(sounds[i], MIX_MAX_VOLUME*0.5f);
    }
    
}

void SoundEffect::Play(int index)
{
     if (Mix_PlayChannel(-1, sounds[index], 0) == -1) {
        std::cerr << "Failed to play sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void SoundEffect::Mute(int index)
{
    Mix_VolumeChunk(sounds[index], 0);
}

void SoundEffect::UnMute(int index)
{
    Mix_VolumeChunk(sounds[index], MIX_MAX_VOLUME);
}

void SoundEffect::SetVolume(float delta)
{
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_VolumeChunk(sounds[i], MIX_MAX_VOLUME*delta);
    }
    
}

SoundEffect::~SoundEffect()
{
    for (int i = 0; i < TOTAL_CHUNK; i++)
    {
        Mix_FreeChunk(sounds[i]);
    }
}