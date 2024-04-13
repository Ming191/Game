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

void SoundEffect::Load(std::string p_path)
{
    sound = Mix_LoadWAV(p_path.c_str());
    if (sound == NULL) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void SoundEffect::Play() 
    {
    if (sound != NULL && Mix_PlayChannel(-1, sound, 0) == -1) {
        std::cerr << "Failed to play sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}