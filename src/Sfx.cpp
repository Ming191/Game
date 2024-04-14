#include<headers/sfx.h>

void MusicPlayer::PlayCurrentTrack() 
{
    if (currIndex >= 0 && currIndex < playList.size()) {
        Mix_Music* music = Mix_LoadMUS(playList[currIndex].first.c_str());
        Mix_PlayMusic(music, -1);
        std::cout << "Now playing: " << playList[currIndex].second << std::endl;
    }
}

void MusicPlayer::NextTrack()
{
    currIndex++;
    if (currIndex >= playList.size()) {
        currIndex = 0; 
    }
    PlayCurrentTrack();
}

void MusicPlayer::PreviousTrack()
{
    currIndex--;
    if(currIndex < 0)
    {
        currIndex = playList.size()-1;
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

SoundEffect::SoundEffect()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    Mix_AllocateChannels(16);
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

void SoundEffect::Mute(int index)
{
    Mix_VolumeChunk(sounds[index], 0);
}

void SoundEffect::UnMute(int index)
{
    Mix_VolumeChunk(sounds[index], MIX_MAX_VOLUME);
}