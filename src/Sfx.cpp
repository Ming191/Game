#include<headers/sfx.h>

void MusicPlayer::PlayCurrentTrack() 
{
    if (currIndex >= 0 && currIndex < playList.size()) {
        Mix_Music* music = Mix_LoadMUS(playList[currIndex].first.c_str());
        Mix_FadeInMusic(music, -1, 5000);
        Mix_PlayMusic(music, 0);
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