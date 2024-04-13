#pragma once

#include<defs.h>

class MusicPlayer
{
private:
    static MusicPlayer* instance;
    std::vector<std::pair<std::string, std::string>> playList =
    {
        {"res/sfx/At The Post Office.mp3", "At The Post Office"},
        {"res/sfx/Contemplation.mp3", "Contemplation"},
        {"res/sfx/Daytime Walking Music.mp3", "Daytime Walking"},
        {"res/sfx/In The Weeds.mp3", "In The Weeds"},
        {"res/sfx/Into The Forest.mp3", "Into The Forest"},
        {"res/sfx/Jazz Bar.mp3", "Jazz Bar"},
        {"res/sfx/On The Case.mp3", "On The Case"},
        {"res/sfx/Pack Your Bags.mp3", "Pack Your Bags"},
        {"res/sfx/Snoopin'.mp3", "Snoopin'"},
        {"res/sfx/Turning Of The Leaves.mp3", "Turning Of The Leaves"}
    };
    int currIndex = 0;
    bool isPlaying = 1;

public:
    MusicPlayer() = default;
    void PlayCurrentTrack();
    void NextTrack();
    void PreviousTrack();
    std::string GetTitle();
    bool IsPlaying(){return isPlaying;};
    void SwitchState(){isPlaying = !isPlaying;};
    void Mute();
    void UnMute();
};

class SoundEffect
{
private:
    std::unordered_map<int, Mix_Chunk*> sounds;
public:
    SoundEffect();
    void Play(int index);
};


